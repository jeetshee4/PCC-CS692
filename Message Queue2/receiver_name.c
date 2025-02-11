#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

struct student_data {
    long mtype;
    char name[50];
    int roll;
};

int compare_names(const void *a, const void *b) {
    return strcmp(((struct student_data *)a)->name, ((struct student_data *)b)->name);
}

int main() {
    key_t key = 12345;
    int msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    struct student_data students[100];
    int count = 0;

    while (1) {
        struct student_data sd;
        if (msgrcv(msgid, &sd, sizeof(sd) - sizeof(long), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        if (sd.roll == -1) break;
        students[count++] = sd;
    }

    qsort(students, count, sizeof(struct student_data), compare_names);

    for (int i = 0; i < count; i++) {
        students[i].mtype = 3;
        if (msgsnd(msgid, &students[i], sizeof(students[i]) - sizeof(long), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
    }

    struct student_data end = {3, "", -1};
    msgsnd(msgid, &end, sizeof(end) - sizeof(long), 0);

    return 0;
}
