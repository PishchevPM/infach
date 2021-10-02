#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
/*This program opens a directory and prints list of this directory's content*/
void main(int argc, char* argv[], char* envp[]) {
  struct dirent * filename;
  DIR * dir;
  /*Opening a directory*/
  if (argc == 1) {
    argv[1] = "/"; /*Default directory - root*/
  }
  if ((dir = opendir(argv[1])) == NULL) {
    printf("Cannot open directory\n");
    exit(-1);
  }
  /*Reading file names with readdir func.*/
  while (1) {
    if ((filename = readdir(dir)) == NULL){
      printf("The end\n");
      exit(0);
    }
    printf("%s\n", filename->d_name);
  }
}
