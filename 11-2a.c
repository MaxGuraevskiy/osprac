#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int msqid;                   // IPC descriptor for the message queue
  char pathname[] = "11-2a.c"; // The file name used to generate the key.
                               // A file with this name must exist in the current directory.
  key_t key;                   // IPC key
  int i, len;                  // Cycle counter and the length of the informative part of the message

  struct mymsgbuf // Custom structure for the message
  {
    long mtype;
    struct
    {
      short sinfo;
      float finfo;
    } info;
  } mybuf;

  if ((key = ftok(pathname, 0)) < 0)
  {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
  {
    printf("Can\'t get msqid\n");
    exit(-1);
  }

  /* Send information */

  for (i = 1; i <= 5; i++)
  {
    mybuf.mtype = 1;
    mybuf.info.sinfo = 666;
    mybuf.info.finfo = 1337.1488;

    len = sizeof(mybuf.info);

    if (msgsnd(msqid, (struct msgbuf *)&mybuf, len, 0) < 0)
    {
      printf("Can\'t send message to queue\n");
      msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
      exit(-1);
    }
  }

  for (int i = 0; i < 5; ++i)
  {
    len = sizeof(mybuf.info);

    if ((len = msgrcv(msqid, &mybuf, len, 2, 0)) < 0)
    {
      printf("Can\'t receive message from queue\n");
      exit(-1);
    }
    printf("type = %ld, sinfo = %d, finfo = %f\n", mybuf.mtype, mybuf.info.sinfo, mybuf.info.finfo);
  }

  return 0;
}