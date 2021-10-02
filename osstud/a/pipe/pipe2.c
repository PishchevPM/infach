#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#define length 14

void main(){
  int fd1[2], fd2[2], result;
  size_t size;
  char resstring1[length];
  char resstring2[length];
  if (pipe(fd1) < 0) {
    printf("Cannot create pipe\n");
    exit(-1);
  }
  if (pipe(fd2) < 0) {
    printf("Cannot create pipe\n");
    exit(-1);
  }
  result = fork();
  if (result < 0) {
    printf("Cannot fork child\n");
    exit(-1);
  } else if (result == 0) {
         /*close(fd[1]);*/
           size = write(fd2[1], "Shit happens.", length);
	   if(size != length) {
	     printf("cannot write all string\n");
	     exit(-1);
	   }
	   size = read(fd1[0], resstring1, length);
	   if (size < 0) {
	     printf("Cannot read string\n");
	     exit(-1);
	   }
	   printf("Child exit\n");
	   printf("%s\n", resstring1);
  } else {
    /*close(fd[0]);*/
      size = read(fd2[0], resstring2, length);
      if (size < 0) {
	printf("Cannot read string\n");
	exit(-1);
      }
      size = write(fd1[1], "Hello, world!", length);
      if(size != length) {
	printf("cannot write all string\n");
	exit(-1);
      }
      printf("Parent exit\n");
      printf("%s\n", resstring2);
  }
}
/*
Parent exit
Child exit
Hello, world!
Shit happens.
*/
