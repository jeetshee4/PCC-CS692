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

//even parity generator 
char * parity_generator(char *data_stream)
{
int count=0;
  for (int i=0 ; i<strlen(data_stream);i++){
    if(data_stream[i] == '1')
    {
      count++;
    }
  
  }
  if (count % 2 != 0)
  {
    return "1";
  }
  else {
    return "0";
  }
}


char * newdata_stream(char * a )
{
   
   
   
   strcat(a,parity_generator(a));
   
   return a;
}

int main ()
{
   int sfd , cfd;
   struct sockaddr_un my_addr, peer_addr;
   socklen_t peer_addr_size;
   
   sfd = socket(AF_UNIX , SOCK_STREAM , 0);
   
   
   
   memset(&my_addr , 0 , sizeof(my_addr));
   
   my_addr.sun_family = AF_UNIX;
   
   strncpy(my_addr.sun_path ,MY_SOCK_PATH, sizeof(my_addr.sun_path) - 1);
   
   
   unlink(MY_SOCK_PATH);
   
   bind(sfd , (struct sockaddr *) &my_addr , sizeof(my_addr));
   
   listen(sfd , LISTEN_BACKLOG);
   
   peer_addr_size = sizeof(peer_addr);
   cfd = accept(sfd , (struct sockaddr *) &peer_addr , &peer_addr_size);
   
   //The code for getting the data stream to the client
   char buf[100];
   read(cfd ,buf ,100 );
   
   printf("The message recieved is: %s", buf);
   
   write (cfd , newdata_stream(buf) , 100);
   
   //Ending of the code for the sending of the data stream to the   client       side  

   
   

 }



