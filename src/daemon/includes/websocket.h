#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

int make_api_request(const char *url, const char* path_cacert);

#endif
