#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/sysinfo.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MTEXT_SIZE 128
//size( mtype(4bytes) + ...  ) < 4056
struct msgbuf {
    long mtype;
    char mtext[MTEXT_SIZE];
};

int main() {
    FILE* f = fopen("../mqid.txt", "r");
    if(f == 0) {
        perror("mqid.txt opening");
        exit(1);
    }
    char text[10];
    int i = 0;
    int mqid[10];
    while(fgets(text, sizeof(text), f) != NULL) {
        mqid[i] = atoi(text);
        i++;
    }

    fclose(f);

    struct msgbuf msg;
    msg.mtype = 1;
    strcpy(msg.mtext, "msg sent");

    if(msgsnd(mqid[1], (void *)&msg, strlen(msg.mtext), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    return 0;
}