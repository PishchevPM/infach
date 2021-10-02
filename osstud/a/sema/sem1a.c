#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>

void main(){
  int semID;
  char pathname[] = "sem1a.c";
  key_t key;
  struct sembuf mybuf;
  if ((key=ftok(pathname,0)) < 0) {
    printf("Cannot generate key\n");
    exit(-1);
  }
  if ((semID = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
    printf("Cannot get semID\n");
    exit(-1);
  }
  mybuf.sem_op = 1;
  mybuf.sem_flg = 0;
  mybuf.sem_num = 0;
  if (semop(semID, &mybuf, 1) < 0) {
    printf("Cannot wait for condition\n");
    exit(-1);
  }
  printf("Condition is set\n");
}
