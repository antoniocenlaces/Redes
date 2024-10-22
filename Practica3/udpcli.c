#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#define MAXLINE 1000

int main(int argc, char **argv)
{
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in  servaddr = { 0 };

    if (argc != 3)
    {
        printf("usage: %s <IPaddress> <puerto>\n", argv[0]);
        exit(0);
    }
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("socket error\n");
        exit(0);
    }
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(atoi(argv[2]));  /* daytime server port*/
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) // convierte la diección argv[1] en binario en el campo sin_addr
    {
        printf("inet_pton error for %s", argv[1]);
        exit(0);
    }
    // UDP no hace connect. solo sendto() recvfrom()
    // if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
    // {
    //     printf("connect error");
    //     exit(0);
    // }
    // servaddr contiene la dirección del servidor
    recvline[0]='?';recvline[1]=0;
    n = sendto(sockfd, recvline, 2,0,(struct sockaddr *) &servaddr, sizeof(servaddr));
    if (n < 0) {
        printf("client sendto error for %s", argv[1]);
        exit(0);
    }
    n = recvfrom(sockfd, recvline, MAXLINE,0,NULL,NULL);
    if (n > 0)
    {
		recvline[n] = 0;    /* null terminate */
        printf("%s\n", recvline);
    }
    exit(0);
}
