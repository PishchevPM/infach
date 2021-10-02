
/* A simple echo UDP server */

#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>

int  sockfd;
char line[1000];
struct sockaddr_in servaddr;

long I = 0;

void handler(int nsig)
{
   int    clilen,n;
   struct sockaddr_in cliaddr;

   clilen = sizeof(cliaddr);
       
   if( ( n = recvfrom(sockfd, line, 999, 0, (struct sockaddr *) &cliaddr, 
   &clilen)) < 0){
      printf("Can\'t receive request, errno = %d\n", errno);
      close(sockfd);
      exit(1);
   }

   sprintf(line, "I=%ld\n", I);
       
   if(sendto(sockfd, line, strlen(line), 0, (struct sockaddr *) &cliaddr, 
   clilen) < 0){
      printf("Can\'t send answer, errno = %d\n", errno);
      close(sockfd);
      exit(1);
   }
    
   signal(SIGIO, handler);
}

int main()
{
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_port        = htons(51000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
       printf("Can\'t create socket, errno = %d\n", errno);
       exit(1);
    }

    if(bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
       printf("Can\'t bind socket, errno = %d\n", errno);
       close(sockfd);
       exit(1);
    }

    signal(SIGIO, handler);
    
    if (fcntl(sockfd, F_SETOWN, getpid()) < 0){
       printf("Can\'t set socket group, errno = %d\n", errno);
       close(sockfd);
       exit(1);
    }

    if (fcntl(sockfd, F_SETFL, FASYNC) < 0){
       printf("Can\'t set socket group, errno = %d\n", errno);
       close(sockfd);
       exit(1);
    }

 
    while(1) {
         I = I+1;       
    }
    
    return 0;
}
