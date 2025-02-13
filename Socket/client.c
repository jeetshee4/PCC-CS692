#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <string.h>
#define MY_SOCK_PATH "./mysocket"
#define LISTEN_BACKLOG 1



int main ()
{
   int sfd , cfd;
   struct sockaddr_un my_addr, peer_addr;
   socklen_t peer_addr_size;
   
   sfd = socket(AF_UNIX , SOCK_STREAM , 0);
   
   
   
   memset(&my_addr , 0 , sizeof(my_addr));
   
   my_addr.sun_family = AF_UNIX;
   
   strcpy(my_addr.sun_path ,MY_SOCK_PATH);
   
   

   connect(sfd , (struct sockaddr *) &my_addr , sizeof(my_addr));
   
   
   
   //The code for sending the data stream from  client to server
   
   char buffer[100];
   
   scanf("%s",buffer);
   
   write (sfd , buffer , strlen(buffer));
   
   read (sfd , buffer ,100);
   
   
   
   printf("char from server = %s\n", buffer);
   //Ending of the code for the sending of the data stream to the   client       side  

   close(sfd);
   

 }



