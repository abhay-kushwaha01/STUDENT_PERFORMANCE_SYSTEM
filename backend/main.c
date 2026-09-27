#include "server.h"
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif
int main(void){
    printf("\n=== Student Performance Analysis System ===\n");
    printf("Backend: C socket server | Frontend: HTML/CSS/JavaScript\n\n");
    if(!server_start()){fprintf(stderr,"Server could not start. Check the error above.\n");return 1;}
    return 0;
}
