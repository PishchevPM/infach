/* A simple echo UDP server */

#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{

    int  sfd1, sfd2, newsockfd, clilen, n;
    char line[1000];
    struct sockaddr_in servaddr, cliaddr;
    fd_set set;
    int nset, maxfd;

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_port        = htons(51000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if((sfd1 = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
       printf("Can\'t create UDP socket, errno = %d\n", errno);
       exit(1);
    }

    if((sfd2 = socket(AF_INET, SOCK_STREAM, 0)) < 0){
       printf("Can\'t create TCP socket, errno = %d\n", errno);
       close(sfd1);
       exit(1);
    }

    if(bind(sfd1, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
       printf("Can\'t bind UDP socket, errno = %d\n", errno);
       close(sfd1);
       close(sfd2);
       exit(1);
    }

    if(bind(sfd2, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
       printf("Can\'t bind TCP socket, errno = %d\n", errno);
       close(sfd1);
       close(sfd2);
       exit(1);
    }

    if(listen(sfd2, 5) < 0){
       printf("Can\'t change state of socket to listen state, errno = %d\n", errno);
       close(sfd1);
       close(sfd2);
       exit(1);
    }

    while(1){
       FD_ZERO(&set);
       FD_SET(sfd1,&set);
       FD_SET(sfd2,&set);
    
       maxfd = ((sfd1 > sfd2) ? sfd1 : sfd2)+1;
       nset=select(maxfd, &set, (fd_set *)NULL, (fd_set *)NULL, (struct timeval *)NULL);
       if(nset < 0) {
          printf("Can\'t wait on select system call, errno = %d\n", errno);
          close(sfd1);
          close(sfd2);
          exit(1);
       }

       while(nset > 0){       
          if(FD_ISSET(sfd1,&set)){
             FD_CLR(sfd1,&set);
             clilen = sizeof(cliaddr);
       
             if( ( n = recvfrom(sfd1, line, 999, 0, (struct sockaddr *) &cliaddr, 
             &clilen)) < 0){
                printf("Can\'t receive request, errno = %d\n", errno);
                close(sfd1);
                close(sfd2);
                exit(1);
             }

             printf("UDP socket %s\n",line);       
             line[n] = '\n'; 
             if(sendto(sfd1, line, strlen(line), 0, (struct sockaddr *) &cliaddr, 
             clilen) < 0){
                printf("Can\'t send answer, errno = %d\n", errno);
                close(sfd1);
                close(sfd2);
                exit(1);
             }
          }   
        
          if(FD_ISSET(sfd2,&set)){
             FD_CLR(sfd2,&set);
	     
             clilen = sizeof(cliaddr);
             if( (newsockfd = accept(sfd2, (struct sockaddr *) &cliaddr, &clilen)) < 0){
                printf("Can\'t accept connection, errno = %d\n", errno);
                close(sfd1);
                close(sfd2);
                exit(1);
             }


             while( (n = read(newsockfd, line, 999)) > 0){
                printf("TCP socket %s\n",line);       
                line[n] = '\n';
                if( (n = write(newsockfd, line, strlen(line)+1)) < 0){
                   printf("Can\'t write, errno = %d\n", errno);
                   close(sfd1);
                   close(sfd2);
                   close(newsockfd);
                   exit(1);
     	        }
             } 

   
             if(n < 0){
                printf("Can\'t read, errno = %d\n", errno);
                close(sfd1);
                close(sfd2);
                close(newsockfd);
                exit(1);
             }	   
             close(newsockfd);
         }
         nset = nset-1;   
      }
   }
   
   return 0;
}
