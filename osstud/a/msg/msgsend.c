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
  int i, j, length;
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
 for (i = 1; i <= 5; i++) {
   mybuf.mtype = 1;
   mybuf.info.rubbish = (i*3);
   mybuf.info.minfo[0] = i;
   for (j=1;j<=9;j++)
     mybuf.info.minfo[j] = i+j;
   length = sizeof(mybuf.info);
   if (msgsnd(msqid, (struct msgbuf*) &mybuf, length, 0) < 0) {
     printf("Cannot send message to queue\n");
     msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
     exit(-1);
   }
 }
 mybuf.mtype = last_msg;
 length = 0;
 if (msgsnd(msqid, (struct msgbuf *) &mybuf, length, 0) < 0) {
   printf("Cannot send final message to queue\n");
   msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
   exit(-1);
 }
}
