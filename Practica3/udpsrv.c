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
#include <time.h>

#define LISTENQ 5
#define MAXLINE 1000

int main(int argc, char **argv)
{
	int	listenfd, n;
	struct sockaddr_in	servaddr =  { 0 };
	struct sockaddr_in cliaddr = {0};
	char buff[MAXLINE];
	time_t ticks;
	socklen_t  len;

    if (argc != 2)
    {
        printf("usage: %s <puerto>\n", argv[0]);
        exit(0);
    }
	listenfd = socket(AF_INET, SOCK_DGRAM, 0);
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(atoi(argv[1]));
	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	// listen(listenfd, LISTENQ); No hay listen() en UDP
	for ( ; ; )
	{	
		len = sizeof(cliaddr); // Set length to size of client address
		n = recvfrom(listenfd,buff,MAXLINE,0, (struct sockaddr *) &cliaddr, &len);
		if (n < 0) {
			printf("server recvfrom error for %s", argv[1]);
        	exit(0);
		}
		if (buff[0]=='?'){
			ticks = time(NULL);
			snprintf(buff, sizeof(buff), "%.24s\n", ctime(&ticks));
			n = sendto(listenfd, buff, strlen(buff),0,(struct sockaddr *) &cliaddr, sizeof(cliaddr));
		}
		if (n < 0) {
			printf("server sendto error for %s", argv[1]);
        	exit(0);
		}
		
	}
}
