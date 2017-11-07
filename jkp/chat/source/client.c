#include "chat_client.h"

int main(void)
{
   int result;
   char buf[BUFSIZ];
   
   ct.client_fd = socket(AF_INET, SOCK_STREAM, 0);
   ct.client_address.sin_family = AF_INET;
   ct.client_address.sin_addr.s_addr = htonl(INADDR_ANY);
   ct.client_address.sin_port = htons(5947);
   ct.client_len = sizeof(ct.client_address);
   result = connect(ct.client_fd, (struct sockaddr *)&(ct.client_address), ct.client_len);

   if (result == -1)
   {
      printf("ERROR : %d,%s\n",errno, strerror(errno));
      return 1;
   }      
   
   
   while(1)
   {
      fgets(buf, BUFSIZ, stdin);
      buf[strlen(buf) - 1] = 0;
      write(ct.client_fd, buf, BUFSIZ);
      if (strncmp(buf, "end", 3) == 0)
         break;
      read(ct.client_fd, buf, BUFSIZ);
      printf("server = %s\n", buf);
      memset(buf, 0, BUFSIZ);
   }
   close(ct.client_fd);
   return 0;
      
}
