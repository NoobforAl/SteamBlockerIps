#include "core.h"
#include "log.h"

static int run_command(char *command, char *per);
static int unblock_ip(char *ip);
static int block_ip(char *ip);

static size_t write_data_response(void *ptr, size_t size, size_t nmemb, void *stream);
static int download_content_about_steam_servers(void);

static char *read_data_from_file_into_buffer(FILE *fp);
static cJSON *get_root_json_data(void);

static int check_is_success_data(cJSON *root);
static int check_block_ips_is_exist(void);

static cJSON *get_relays_from_symbol_object(cJSON *pops, const char *symbol);
static cJSON *get_ipv4_from_relay_with_index(cJSON *relays, size_t index);

int enable_ips(void)
{
    log_info("remove ips form list! (list is a file: %s )", BLOCK_IPS);

    FILE *file = fopen(BLOCK_IPS, "r");
    if (file == NULL)
    {
        log_error("can't open %s file!", BLOCK_IPS);
        return ERR_OPEN_FILE;
    }

    char *line = NULL;
    size_t len = 0;
    int i = 0;

    while (getline(&line, &len, file) != -1)
    {
        if (++i < 2)
            continue;
        if (strlen(line) < 5)
            continue;
        if (line[len - 1] == '\n')
            line[len - 1] = 0;

        if (unblock_ip(line) != OK)
            log_warn("can't run command ! ( check stdout )");
    }

    log_info("run system ufw status !");
    system("sudo ufw status");
    return OK;
}

int disable_ips(const int argc, const char **argv)
{
    int rc = download_content_about_steam_servers();
    if (rc != OK)
        return NOT_OK;

    cJSON *root = get_root_json_data();
    if (root == NULL)
        return ERR_PARS_JSON;

    rc = check_is_success_data(root);
    if (rc != OK)
    {
        cJSON_Delete(root);
        return NOT_OK;
    }

    cJSON *pops = cJSON_GetObjectItemCaseSensitive(root, "pops");
    if (pops == NULL)
    {
        log_error("not successful read data in file please check it");
        cJSON_Delete(root);
        return NOT_OK;
    }

    rc = check_block_ips_is_exist();
    if (rc != OK)
        return NOT_OK;

    log_info("Start block ips!");

    FILE *blocks_ips_file = fopen(BLOCK_IPS, "w");
    if (!blocks_ips_file)
    {
        log_error("can't open %s file!", BLOCK_IPS);
        cJSON_Delete(root);
        return ERR_OPEN_FILE;
    }

    fprintf(blocks_ips_file, "#!! Don't remove this File !!\n\n");

    // if get any error for bad args, loop skip!
    for (size_t i = 2; i < argc; i++)
    {
        cJSON *relays = get_relays_from_symbol_object(pops, argv[i]);
        if (relays == NULL)
            continue;

        int array_size = cJSON_GetArraySize(relays);
        for (int i = 0; i < array_size; i++)
        {
            cJSON *ipv4 = get_ipv4_from_relay_with_index(relays, i);
            if (ipv4 == NULL)
                continue;

            log_warn("Block Ip: %s", ipv4->valuestring);
            fprintf(blocks_ips_file, "%s\n", ipv4->valuestring);

            if (block_ip(ipv4->valuestring) != OK)
                log_warn("can't run this command! ( check stdout )");
        }
    }

    log_info("run system firewall status !");
    system("sudo ufw status");
    fclose(blocks_ips_file);
    cJSON_Delete(root);
    return OK;
}

static int run_command(char *command, char *per)
{
    int rc = 0;
    char buf[1024];
    sprintf(buf, command, per);

    log_warn("run command: %s", buf);
    log_info("---------------OutPutCommand---------------\n");
    rc = system(buf);

    printf("\n\n");

    return rc;
}

static int block_ip(char *ip)
{
    char *action;
#if _WIN32
    action = ""; // TODO  add action to block ip in windows!
#else
    action = "sudo ufw deny from %s";
#endif
    return run_command(action, ip);
}

static int unblock_ip(char *ip)
{
    char *action;
#if _WIN32
    action = ""; // TODO  add action to unblock ip in windows!
#else
    action = "sudo ufw delete deny from %s";
#endif
    return run_command(action, ip);
}

static size_t write_data_response(void *ptr, size_t size, size_t nmemb, void *stream)
{
    FILE *fp = (FILE *)stream;
    return fwrite(ptr, size, nmemb, fp);
}

static int download_content_about_steam_servers(void)
{
    log_info("start request to get data server");

    CURL *curl = curl_easy_init();
    if (!curl)
    {
        log_error("can't init curl for request!");
        return ERR_INIT_CURL;
    }

    FILE *file = fopen(PATH_FILE_JSON_DATA_REQ, "w");
    if (!file)
    {
        log_error("can't open %s file", PATH_FILE_JSON_DATA_REQ);
        curl_easy_cleanup(curl);
        return ERR_OPEN_FILE;
    }

    curl_easy_setopt(curl, CURLOPT_URL, API_SERVERS_INFO);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data_response);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

    int rc = curl_easy_perform(curl);
    if (rc != CURLE_OK)
    {
        fclose(file);
        curl_easy_cleanup(curl);
        log_error("curl_easy_perform failed: %s", curl_easy_strerror(rc));
        return ERR_GET_DATA;
    }

    curl_easy_cleanup(curl);
    fclose(file);
    return OK;
}

static char *read_data_from_file_into_buffer(FILE *fp)
{
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);

    fseek(fp, 0, SEEK_SET);
    char *buffer = (char *)malloc(file_size + 1);

    fread(buffer, 1, file_size, fp);
    buffer[file_size] = '\0';

    return buffer;
}

static cJSON *get_root_json_data(void)
{
    FILE *file = fopen(PATH_FILE_JSON_DATA_REQ, "r");
    if (!file)
    {
        log_error("can't open %s file!", PATH_FILE_JSON_DATA_REQ);
        return NULL;
    }

    log_info("pars json data\n");

    char *buffer_data = read_data_from_file_into_buffer(file);
    fclose(file);

    cJSON *root = cJSON_Parse(buffer_data);
    if (!root)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        log_error("can't pars json file, err: %s", error_ptr);
        free(buffer_data);
        return NULL;
    }

    free(buffer_data);
    return root;
}

static int check_is_success_data(cJSON *root)
{
    cJSON *success = cJSON_GetObjectItemCaseSensitive(root, "success");
    if (success == NULL || !cJSON_IsBool(success) || !success->valueint)
    {
        log_error("not successful read data in file please check it!");
        return NOT_OK;
    }

    return OK;
}

static int check_block_ips_is_exist(void)
{
    if (access(BLOCK_IPS, F_OK) != -1)
    {
        log_error("The file does exist! can't run app!");
        log_error("check file, if are you sure remove file and run again app!");
        return NOT_OK;
    }

    return OK;
}

static cJSON *get_relays_from_symbol_object(cJSON *pops, const char *symbol)
{
    cJSON *element = cJSON_GetObjectItem(pops, symbol);
    if (!element)
        return NULL;

    cJSON *desc = cJSON_GetObjectItem(element, "desc");
    if (!desc)
        return NULL;

    cJSON *relays = cJSON_GetObjectItemCaseSensitive(element, "relays");
    if (!relays || !cJSON_IsArray(relays))
        return NULL;

    return relays;
}

static cJSON *get_ipv4_from_relay_with_index(cJSON *relays, size_t index)
{
    cJSON *relay = cJSON_GetArrayItem(relays, index);
    if (relay == NULL)
        return NULL;

    cJSON *ipv4 = cJSON_GetObjectItemCaseSensitive(relay, "ipv4");
    if (!ipv4 || !cJSON_IsString(ipv4))
        return NULL;

    return ipv4;
}
