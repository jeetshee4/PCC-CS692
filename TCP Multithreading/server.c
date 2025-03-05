#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX 100
#define IP "127.0.0.1"
#define PORT 1234

// Function to validate an IPv4 address
int isValidIPv4(const char *ip) {
    struct sockaddr_in sa;
    return inet_pton(AF_INET, ip, &(sa.sin_addr)) != 0;
}

// Thread function to handle each client
void* clientHandler(void* args) {
    int ts = *((int *)args);
    char buff[MAX];

    while(1) {
        memset(buff, 0, MAX);
        read(ts, buff, MAX);
        
        printf("Received from client: %s\n", buff);

        if (strncmp(buff, "exit", 4) == 0) break;

        // Validate IPv4 address
        char response[MAX];
        if (isValidIPv4(buff)) {
            strcpy(response, "YES");
        } else {
            strcpy(response, "NO");
        }

        write(ts, response, strlen(response) + 1);
    }

    close(ts);
    return NULL;
}

int main() {
    int ss = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in saddr, caddr;
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr(IP);
    saddr.sin_port = htons(PORT);

    bind(ss, (struct sockaddr *)&saddr, sizeof(saddr));
    listen(ss, 5);

    printf("Server started on %s:%d\n", IP, PORT);

    while (1) {
        pthread_t th;
        int len = sizeof(caddr);
        int ts = accept(ss, (struct sockaddr *)&caddr, &len);
        pthread_create(&th, NULL, clientHandler, (void*)&ts);
        pthread_detach(th);
    }

    close(ss);
    return 0;
}

