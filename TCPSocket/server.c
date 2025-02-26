#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
void main () {

  int server_sockfd , client_sockfd;
 
  
  
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;
  
  
  server_sockfd = socket(AF_INET , SOCK_STREAM , 0);

  server_address.sin_family=AF_INET;

  server_address.sin_addr.s_addr=inet_addr("127.0.0.1");

  server_address.sin_port=htons(1234);
  
  int server_len , client_len;
   server_len=sizeof(server_address);
  
  
  bind(server_sockfd , (struct sockaddr *)&server_address , server_len);
  
  listen (server_sockfd , 1);
  
  printf("Server is waiting..\n");
  
  while (1) {
  
     
    
    client_len = sizeof(client_address);
    client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len);
    
      char messg2[100];
      char messg3[100];
      read(client_sockfd, messg2, 100);
      
      //Logic for the 0 insertion into the string
      
      int k=0;
      int count=0;
      
      for (int i=0; i< strlen(messg2) ; i++)
      {
         if(messg2[i]=='0')
         {
           count=0;
           messg3[k]=messg2[i];
           k++;   
         }
         else if(messg2[i]=='1') {
           count++;
           
           messg3[k]=messg2[i];
           k++;
           if(count==5)
           {
             messg3[k]='0';
             count=0;
             k++;
             if(i==strlen(messg2))
              i++;
           
           } 
         }      
      }
      
      messg3[k]='\0';
      
      
      
      
   
      
      write(client_sockfd,messg3 ,strlen(messg3)+1);
  
      
      printf("Message sent to Client..\n");
  
  
  
     close(client_sockfd);
  }













}
