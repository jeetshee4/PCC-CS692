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

int main() {
    key_t key = 12345;
    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    int N;
    printf("Enter number of students: ");
    scanf("%d", &N);

    struct student_data sd;

    for (int i = 0; i < N; i++) {
        printf("Enter name and roll for student %d: ", i+1);
        scanf("%s %d", sd.name, &sd.roll);
        sd.mtype = 1;
        if (msgsnd(msgid, &sd, sizeof(sd) - sizeof(long), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
        sd.mtype = 2;
        if (msgsnd(msgid, &sd, sizeof(sd) - sizeof(long), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
    }

    // Send end markers
    sd.mtype = 1;
    sd.roll = -1;
    strcpy(sd.name, "");
    msgsnd(msgid, &sd, sizeof(sd) - sizeof(long), 0);

    sd.mtype = 2;
    msgsnd(msgid, &sd, sizeof(sd) - sizeof(long), 0);

    // Receive sorted by name (mtype3)
    struct student_data sorted;
    int received = 0;
    struct student_data *sorted_names = malloc(N * sizeof(struct student_data));
    while (1) {
        if (msgrcv(msgid, &sorted, sizeof(sorted) - sizeof(long), 3, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        if (sorted.roll == -1) break;
        sorted_names[received++] = sorted;
    }

    printf("\nSorted by name:\n");
    for (int i = 0; i < received; i++)
        printf("%s %d\n", sorted_names[i].name, sorted_names[i].roll);

    // Receive sorted by roll (mtype4)
    received = 0;
    struct student_data *sorted_rolls = malloc(N * sizeof(struct student_data));
    while (1) {
        if (msgrcv(msgid, &sorted, sizeof(sorted) - sizeof(long), 4, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        if (sorted.roll == -1) break;
        sorted_rolls[received++] = sorted;
    }

    printf("\nSorted by roll:\n");
    for (int i = 0; i < received; i++)
        printf("%s %d\n", sorted_rolls[i].name, sorted_rolls[i].roll);

    msgctl(msgid, IPC_RMID, NULL);
    free(sorted_names);
    free(sorted_rolls);

    return 0;
}
