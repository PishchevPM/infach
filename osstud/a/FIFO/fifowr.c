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
    fd = open(name, O_WRONLY);
    if (fd < 0) {
      printf("Cannot open FIFO\n");
      exit(-1);
    }
    size = write(fd, "Hello, world!", length);
    if(size != length) {
      printf("cannot write all string\n");
      exit(-1);
    }
    close(fd);
}
