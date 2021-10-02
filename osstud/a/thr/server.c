#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
/*This server is reacting on type 1 messages
??? How to get client's ID ???
*/

void main() {
  int msqid;
  char pathname[] = "server.c";
  key_t key;
  int i, length, maxlen;
  char ansstr[] = "";
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
 maxlen = 81;
 while(0 == 0) {
   if ((length = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 1, 0)) < 0) {
     printf("Cannot recieve text message from queue\n");
     exit(-1);


   }
   /*   port = getpid();*/
   printf("Info = %s\n", mybuf.mtext);
   mybuf.mtype = port;
   
   strcpy(mybuf.mtext, "Answer from server"+ansstr);
   length = strlen(mybuf.mtext)+1;
   if (msgsnd(msqid, (struct msgbuf*) &mybuf, length, 0) < 0) {
     printf("Cannot send message to queue\n");
     msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
     exit(-1);
   }
   strcpy(mybuf.mtext, "");
   if (msgsnd(msqid, (struct msgbuf*) &mybuf, length, 0) < 0) {
     printf("Cannot send message to queue\n");
     msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
     exit(-1);
   }
 }
 /*msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
   printf("End of the client's transmission\n");*/

}
