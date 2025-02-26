#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
void main () {
  	int sockfd;
	int len;
	struct sockaddr_in client_address;
	int result;
	
       sockfd = socket(AF_INET, SOCK_STREAM, 0);
         client_address.sin_family = AF_INET;
	 client_address.sin_addr.s_addr=inet_addr("127.0.0.1");
         client_address.sin_port=htons(1234);
	 int client_len = sizeof(client_address);
         result = connect(sockfd, (struct sockaddr *)&client_address, client_len);
         //Logic for the message 
         char messg[100];
         char messg1[100];
         printf("Enter the Message: ");
         scanf("%s",messg);
         
         
         
         
         
         write(sockfd, messg, strlen(messg));
         
         printf("Message sent to the server...\n");
	read(sockfd,messg1 ,100);
	
	printf("Returned server :%s \n", messg1);
	close(sockfd);
	
}
