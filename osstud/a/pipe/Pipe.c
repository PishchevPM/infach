#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#define length 14

void main(){
  int fd[2], result;
  size_t size;
  char resstring[length];
  /*cr8 pipe*/
  if (pipe(fd) < 0) {
    printf("Cannot create pipe\n");
    exit(-1);
  }
  result = fork();
  if (result < 0) {
    printf("Cannot fork child\n");
    exit(-1);
  } else if (result == 0) {
           close(fd[1]);
	   size = read(fd[0], resstring, length);
	   if (size < 0) {
	     printf("Cannot read string\n");
	     exit(-1);
	   }
	   printf("Child exit\n");
	   printf("%s\n", resstring);
  } else {
      close(fd[0]);
      size = write(fd[1], "Hello, world!", length);
      if(size != length) {
	printf("cannot write all string\n");
	exit(-1);
      }
      printf("Parent exit\n");
  }
}
/*
Parent exit
Child exit
Hello, world!
*/
