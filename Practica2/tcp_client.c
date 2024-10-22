#include <stdio.h>      // For printf and related functions
#include <stdlib.h>     // For exit function
#include <string.h>     // For memset and other string handling
#include <sys/types.h>  // For data types used in sockets
#include <sys/socket.h> // For socket functions
#include <arpa/inet.h>  // For inet_pton function
#include <unistd.h>     // For close and read functions


int main( int argc , char * argv[] )
{
const int MAXLINE=1024;
int sockfd , n ;
char recvline[MAXLINE + 1 ] ;
struct sockaddr_in servaddr = { 0 };

if ( argc != 3)
{
printf ("usage: %s <IPaddress> <puerto>\n", argv [ 0 ] ) ;
exit (0) ;
}
if ( ( sockfd = socket (AF_INET, SOCK_STREAM, 0) ) < 0)
{
printf ("socket error\n") ;
exit (0) ;
}
servaddr . sin_family = AF_INET;
servaddr . sin_port = htons ( atoi ( argv [ 2 ] ) ) ;
if ( inet_pton (AF_INET, argv [ 1 ] , &servaddr . sin_addr ) <= 0) // convierte la diección argv[1] en binario en el campo sin_addr
{
printf ("inet_pton error for %s", argv [ 1 ] ) ;
exit (0) ;
}
if ( connect ( sockfd , ( struct sockaddr *) &servaddr , sizeof ( servaddr ) ) < 0)
{
printf ("connect error") ;
exit (0) ;
}
n = read ( sockfd , recvline , MAXLINE) ;
if (n > 0)
{
recvline [ n ] = 0; /* n u l l terminate */
printf ("%s\n", recvline ) ;
}
exit (0) ;
}