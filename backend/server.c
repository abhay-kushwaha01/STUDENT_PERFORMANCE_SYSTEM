#include "server.h"
#include "router.h"
#include "file_manager.h"
#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <errno.h>
#endif
static socket_t g_server = INVALID_SOCKET;
void server_stop(void){
    if(g_server!=INVALID_SOCKET){CLOSE_SOCKET(g_server);g_server=INVALID_SOCKET;}
#ifdef _WIN32
    WSACleanup();
#endif
}
static void serve_loop(void){
    char buf[BUFFER_SIZE+1];
    while(1){
        struct sockaddr_in caddr;
#ifdef _WIN32
        int clen=sizeof(caddr);
#else
        socklen_t clen=sizeof(caddr);
#endif
        socket_t c=accept(g_server,(struct sockaddr*)&caddr,&clen);
        if(c==INVALID_SOCKET) break;
        int n=(int)recv(c,buf,BUFFER_SIZE,0);
        if(n>0){
            buf[n]='\0';
            char method[16]={0},path[2048]={0};
            sscanf(buf,"%15s %2047s",method,path);
            char *hdr_end=strstr(buf,"\r\n\r\n");
            char *body=hdr_end?hdr_end+4:NULL;
            route_request(c,method,path,buf,body?body:"");
        }
        CLOSE_SOCKET(c);
    }
}
int server_start(void){
    fm_init();
#ifdef _WIN32
    WSADATA w;
    if(WSAStartup(MAKEWORD(2,2),&w)!=0){fprintf(stderr,"WSAStartup failed\n");return 0;}
#endif
    g_server=socket(AF_INET,SOCK_STREAM,0);
    if(g_server==INVALID_SOCKET){perror("socket");server_stop();return 0;}
    int opt=1;
#ifdef _WIN32
    setsockopt(g_server,SOL_SOCKET,SO_REUSEADDR,(const char*)&opt,sizeof(opt));
#else
    setsockopt(g_server,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
#endif
    struct sockaddr_in addr;memset(&addr,0,sizeof(addr));addr.sin_family=AF_INET;addr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);addr.sin_port=htons(SERVER_PORT);
    if(bind(g_server,(struct sockaddr*)&addr,sizeof(addr))<0){perror("bind");server_stop();return 0;}
    if(listen(g_server,16)<0){perror("listen");server_stop();return 0;}
    printf("Student Performance System running at http://localhost:%d\n",SERVER_PORT);
    serve_loop();
    server_stop();
    return 1;
}
