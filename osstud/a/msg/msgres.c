#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#define last_msg 255
void main() {
  int msqid;
  char pathname[] = "msgsend.c";
  key_t key;
  int i, length, maxlen;
struct mymsgbuf
{
  long mtype;
  struct {
    int minfo[10];
    float rubbish;
  } info;
} mybuf;
 if ((key = ftok(pathname, 0)) < 0) {
   printf("Cannot generate key\n");
   exit(-1);
 }
 if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
   printf("Cannot get msqID\n");
   exit(-1);
 }
 while (0 == 0) {
   maxlen = sizeof(mybuf.info);
   if ((length = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 0, 0)) < 0) {
     printf("Cannot recieve text message from queue\n");
     exit(-1);
   }
   if (mybuf.mtype == last_msg) {
     msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
     printf("End of the transmission\n");
     exit(0);
   }
   printf("Message type = %d, info = ", mybuf.mtype);
   for (i=0;i<=9;i++) {
     printf("%d ", mybuf.info.minfo[i]);
   }
   printf("\n");
 }
}

