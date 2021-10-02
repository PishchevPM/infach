
/* A simple echo TCP server */

#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main()
{
    int    sockfd, newsockfd, clilen, n;
    char   line[1000];
    struct sockaddr_in servaddr, cliaddr;
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_port        = htons(51000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
       printf("Can\'t create socket, errno = %d\n", errno);
       exit(1);
    }

    if(bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
       printf("Can\'t bind socket, errno = %d\n", errno);
       close(sockfd);
       exit(1);
    }

    if(listen(sockfd, 5) < 0){
       printf("Can\'t change state of socket to listen state, errno = %d\n", errno);
       close(sockfd);
       exit(1);
    }

    clilen = sizeof(cliaddr);
        
    if( (newsockfd = accept(sockfd, (struct sockaddr *) &cliaddr, &clilen)) < 0){
       printf("Can\'t accept connection, errno = %d\n", errno);
       close(sockfd);
       exit(1);
    }
    close(sockfd);
    n = read(newsockfd, line, 999);
    line[n] = '\n';
    line[n+1] = '\0';
    printf("%s",line);
    close(newsockfd);
    return 0;
}