#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX 100
#define IP "127.0.0.1"
#define PORT 1234

int main() {
    int cs = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr(IP);
    saddr.sin_port = htons(PORT);

    connect(cs, (struct sockaddr *)&saddr, sizeof(saddr));

    while(1) {
        char buff[MAX], response[MAX];

        printf("Enter an IPv4 address (or type 'exit' to quit): ");
        fgets(buff, MAX, stdin);
        buff[strlen(buff)-1] = '\0';  // Remove newline character

        write(cs, buff, MAX);
        if (strncmp(buff, "exit", 4) == 0) break;

        read(cs, response, MAX);
        printf("Server response: %s\n", response);
    }

    close(cs);
    return 0;
}

