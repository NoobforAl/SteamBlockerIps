#include "version.h"
#include "core.h"
#include "log.h"

int main(const int argc, const char **argv)
{
    print_banner();
    if (argc < 2)
    {
        print_help();
        return OK;
    }

    const char *action = argv[1];
    if (!strcmp(action, "enable"))
        return enable_ips() ? NOT_OK : OK;

    else if (!strcmp(action, "disable"))
        return disable_ips(argc, argv) ? NOT_OK : OK;

    print_help();
    log_error("not found this action!");
    return NOT_OK;
}
