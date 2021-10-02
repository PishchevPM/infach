#include <sys/types.h>
#include <stdio.h>

void main() {
  pid_t pid, ppid;
  pid = getpid();
  ppid = getppid();
  printf("Proc. PID =  %d,  parent's PID =  %d\n", pid, ppid);
}

