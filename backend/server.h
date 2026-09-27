#ifndef SERVER_H
#define SERVER_H

#define SERVER_PORT 8080
#define BUFFER_SIZE 32768

#ifdef _WIN32
#include <winsock2.h>
typedef SOCKET socket_t;
#define CLOSE_SOCKET closesocket
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
typedef int socket_t;
#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)
#define CLOSE_SOCKET close
#endif

int server_start(void);
void server_stop(void);

#endif
