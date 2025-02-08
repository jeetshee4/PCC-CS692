#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msgq.h"
#define N 132
#define key 1234


int main() {
    int msgid = msgget(key, IPC_CREAT | 0666);
    MQ msg;

    msgrcv(msgid, &msg, N, 3, 0);
    printf("Hexadecimal: %s\n", msg.md);

    return 0;
}

