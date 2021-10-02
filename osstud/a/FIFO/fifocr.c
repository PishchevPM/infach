#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#define length 14

void main(){
  int fd, result;
  size_t size;
  char resstring[length];
  char name[] = "ff.fifo";
  result = fork();
  if (result < 0) {
    printf("Cannot fork child\n");
    exit(-1);
  } else if (result == 0) {
    fd = open(name, O_RDONLY);
    if (fd < 0) {
      printf("Cannot open FIFO in child\n");
      exit(-1);
    }
    size = read(fd, resstring, length);
    if (size < 0) {
      printf("Cannot read string\n");
      exit(-1);
    }
    printf("%s\n", resstring);
    close(fd);
  } else {
    fd = open(name, O_WRONLY);
    if (fd < 0) {
      printf("Cannot open FIFO in parent\n");
      exit(-1);
    }
    size = write(fd, "Hello, world!", length);
    if(size != length) {
      printf("cannot write all string\n");
      exit(-1);
    }
    close(fd);
    printf("Parent exit\n");
  }
}
/*
Parent exit
Hello, world!
*/
