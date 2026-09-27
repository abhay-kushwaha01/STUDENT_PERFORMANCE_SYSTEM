#ifndef ROUTER_H
#define ROUTER_H
#include "server.h"
void route_request(socket_t client,const char*method,const char*path,const char*headers,const char*body);
#endif
