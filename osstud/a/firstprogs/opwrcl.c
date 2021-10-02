#include <sys/types.h>
/*#include <unistd.h>*/
#include <stdio.h>
#include <fcntl.h>
#define length 14
void main(){
  int fd;
  size_t size;
  char string[] ="Hello, world";
  fd = open("myfile", O_WRONLY | O_CREAT);
  size = write(fd, string, length);
  if (size != 14) {
    printf("Cannot write all string\n");
  }
  close(fd);
}
/*
... [23:17pm] ALESHA[10089]more myfile 
Hello, world
*/
