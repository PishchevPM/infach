#include <signal.h>
/*To stop this process u need to kill it from another terminal*/
int i = 0;
void * myint(int nsig){
  if (nsig == 2) {
    printf("No way. You cannot stop me\n");
  }
  if (nsig == 3) {
    printf("HAHA! YOU CANNOT KILL ME!\n");
  }
  i++;
  if (i>=20) {
    printf("Ok, I'm tired. Go fuck with something else.\n");
    exit(0);
  }
}

void main() {
  printf("Ok, lets begin. I beg that you cannot get out of there\n");
  (void)signal(SIGINT, myint);
  (void)signal(SIGQUIT, myint);
  while (1);
}
