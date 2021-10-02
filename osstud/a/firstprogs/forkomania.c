#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#define MANY 100000
int main() {
  int i;
  for (i = 1;i<=MANY;i++){
    fork();
  }
  return 0;
}
