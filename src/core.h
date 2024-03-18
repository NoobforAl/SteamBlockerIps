#ifndef CORE
#define CORE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <unistd.h>
#include <string.h>
#include <strings.h>

#include <curl/curl.h>
#include <cjson/cJSON.h>

#define OK 0
#define NOT_OK 1
#define ERR_INIT_CURL 2
#define ERR_OPEN_FILE 3
#define ERR_GET_DATA 4
#define ERR_PARS_JSON 5
#define ERR_SYMBOL_NOT_VALID 6

#define PATH_FILE_JSON_DATA_REQ "./data.json"
#define BLOCK_IPS "./blockips.txt"

// TODO fix for any game, in this time work for CS2 game with appid 730
#define API_SERVERS_INFO "https://api.steampowered.com/ISteamApps/GetSDRConfig/v1/?appid=730"

// remove ip blocked in firewall
//
// first read `BLOCK_IPS` file,
// get ips block in firewall, at last remove ips in firewall
//
// !Note: Don't remove blockips.txt file!
//
// this file remmber what is you block in firewall
int enable_ips(void);

// add ips to firewall blocked
//
// fire request to `API_SERVERS_INFO` and get json data,
// save in `PATH_FILE_JSON_DATA_REQ` and read data,
// use symbol you send in args, get json data,
// for each exist symbol key in object json,
// finally block ips in firewall
int disable_ips(const int argc, const char **argv);

#endif