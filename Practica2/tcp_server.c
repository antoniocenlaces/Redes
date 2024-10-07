#include <stdio.h>      // For printf and related functions
#include <stdlib.h>     // For exit function
#include <string.h>     // For memset and other string handling
#include <sys/types.h>  // For data types used in sockets
#include <sys/socket.h> // For socket functions
#include <arpa/inet.h>  // For inet_pton function
#include <unistd.h>     // For close and read functions

int main( int argc , char * argv[] ) {
    const int MAXLINE=1024;
    const int LISTENQ = 512;
    int listenfd, connfd;
    struct sockaddr_in servaddr = { 0 };
    char buff[MAXLINE];
    time_t ticks;

    if (argc != 2){
        printf("usage: %s <puerto>\n", argv[0]);
        exit(0);
    }

    listenfd = socket(AF_INET, SOCK_STREAM, 0); // Establece un socket TCP en ipv4
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(atoi(argv[1]));

    bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    listen(listenfd, LISTENQ);

    for ( ; ; ){
        connfd =accept(listenfd, (struct sockaddr *) NULL, NULL);
        ticks = time(NULL);
        sprintf(buff, sizeof(buff), "%.24s\n", ctime(&ticks));
        write(connfd, buff, strlen(buff));
        close(connfd);
    }

}