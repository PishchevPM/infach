#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#define last_msg 255
void main() {
  int msqid;
  char pathname[] = "msgsend_txt.c";
  key_t key;
  int i, length;
struct mymsgbuf
{
  long mtype;
  char mtext[80];
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
   strcpy(mybuf.mtext, "Test");
   length = strlen(mybuf.mtext)+1;
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
