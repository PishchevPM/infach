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
  fd = open(name, O_RDONLY | O_NDELAY);
  if (fd < 0) {
    printf("Cannot open FIFO\n");
    exit(-1);
  }
  size = read(fd, resstring, length);
  if (size < 0) {
    printf("Cannot read string\n");
    exit(-1);
  }
  printf("%s\n", resstring);
  close(fd);

}
/* Not working - wtf?*/
