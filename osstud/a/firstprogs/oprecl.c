#include <sys/types.h>
/*#include <unistd.h>*/
#include <stdio.h>
#include <fcntl.h>
#define length 14
void main(){
  int fd;
  size_t size;
  char string[length];
  fd = open("myfile", O_RDONLY | O_CREAT);
  size = read(fd, string, length);
  printf("%s\n%d\n", string, size);
  close(fd);
}

/*Hello, world
  14*/
