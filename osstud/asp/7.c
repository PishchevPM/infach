
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>

long I = 0;


void handler(int nsig)
{
   int    clilen,n;

   printf("I=%ld\n", I);
       
   signal(SIGIO, handler); 
   
   
   
   
}

int main()
{
    signal(SIGIO, handler);
    
    if (fcntl(0, F_SETOWN, getpid()) < 0){
       printf("Can\'t set socket group, errno = %d\n", errno);
       exit(1);
    }

    if (fcntl(0, F_SETFL, FASYNC) < 0){
       printf("Can\'t set socket group, errno = %d\n", errno);
       exit(1);
    }

 
    while(1) {
         I = I+1;       
    }
    
    return 0;
}
