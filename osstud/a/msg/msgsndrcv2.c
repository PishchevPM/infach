#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#define last_msg 255
void main() {
  int msqid;
  char pathname[] = "msgsndrcv1.c";
  key_t key;
  int i, length, maxlen;
struct mymsgbuf
{
  long mtype;
  char mtext[81];
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
   mybuf.mtype = 2;
   strcpy(mybuf.mtext, "Test text message (prog N2)");
   length = strlen(mybuf.mtext)+1;
   if (msgsnd(msqid, (struct msgbuf*) &mybuf, length, 0) < 0) {
     printf("Cannot send message to queue\n");
     msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
     exit(-1);
   }
 }
 strcpy(mybuf.mtext, "");
 if (msgsnd(msqid, (struct msgbuf*) &mybuf, length, 0) < 0) {
   printf("Cannot send message to queue\n");
   msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
   exit(-1);
 }
 while (0 == 0) {
   maxlen = 81;
   if ((length = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 1, 0)) < 0) {
     printf("Cannot recieve text message from queue\n");
     exit(-1);
   }
   length = strlen(mybuf.mtext)+1;
   if (length == 1) {
     printf("End of the transmission1->2\n");
     mybuf.mtype = last_msg;
     strcpy(mybuf.mtext, "The End");
     length = strlen(mybuf.mtext)+1;
     if (msgsnd(msqid, (struct msgbuf*) &mybuf, length, 0) < 0) {
       printf("Cannot send last message to queue\n");
       msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
       exit(-1);
     }
     exit(0);
   }
   printf("message type = %d, info = %s\n", mybuf.mtype, mybuf.mtext);
 }
}
