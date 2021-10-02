#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>
#define MANY 100000
/*NAEBKA!*/
void main(){
  int fd; /*file descriptor*/
  size_t length;
  int i;
  struct Sh {
    double f;
    double f2;
  } *ptr, *tmpptr;
  fd = open("mapped.dat", O_RDWR | O_CREAT, 0666);/*mbe mmap?*/
  if (fd == -1) {
    printf("Cannot create/open file\n");
    exit(-1);
  }
  length = MANY*sizeof(struct Sh);
  ftruncate(fd, length);
  close(fd);
  printf ("%d\n", ptr->f);
  if (ptr == MAP_FAILED) {
    printf("Mapping failed:(\n");
    exit(-1);
  }
  
  tmpptr = ptr;
  for(i = 1; i <= MANY-1; i++){
    printf("%d\n", i);
    tmpptr->f = (double)i;
    tmpptr->f2 = tmpptr->f*tmpptr->f;
    tmpptr++;
  }
  munmap((void *)ptr, length);
}
