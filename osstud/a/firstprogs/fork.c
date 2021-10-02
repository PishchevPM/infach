#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  pid_t pid, ppid;
  int a = 0;
  pid = fork();  
  if (pid == -1) {
    printf("Fuck you:");
  }  else  if (pid==0){
    a = a+1;
    pid = getpid();
    ppid = getppid();
    printf("\nI'm so fuckin happy xD\n"); 
   printf("Proc. PID =  %d,  parent's PID =  %d, result = %d\n", pid, ppid, a);
  }  else {
    pid = getpid();
    ppid = getppid();
    printf("\nLeave me alone pls >:|\n");
   printf("Proc. PID =  %d,  parent's PID =  %d, result = %d\n", pid, ppid, a);
  }
  return 0;
}

/*Leave me alone pls >:|
Proc. PID =  8861,  parent's PID =  7977, result = 0

I'm so fuckin happy xD
Proc. PID =  8862,  parent's PID =  1, result = 1*/
