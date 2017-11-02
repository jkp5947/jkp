#include "chat_server.h"

void recv_id(jkp_global *global_data, char *recv_id)
{

}

void send_list(jkp_global *global_data, int request_fd)
{

}

int inv_request(jkp_global *global_data, char *id)
{
   
}

void send_inv(jkp_global *global_data, int inv_fd)
{

}

void call_history(jkp_global *global_data, int request_fd)
{

}

void exit_client(jkp_global *global_data, int exit_client_fd)
{

}

int main(void)
{
   int server_sockfd;
   int server_len;
   struct sockaddr_in server_address;
   struct sockaddr_in client_address;
   int result, i;
   int cnt = 0;
   int nfds = 4;
   Client_data c_data;
   fd_set readfds, testfds;
   
   server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
   server_address.sin_family = AF_INET;
   server_address.sin_addr.s_addr = htonl(INADDR_ANY);
   server_address.sin_port = htons(5947);
   server_len = sizeof(server_address);

   bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

   listen(server_sockfd, 10);
   FD_ZERO(&readfds);
   FD_SET(server_sockfd, &readfds);

   while (1)
   {
      char buf[BUFSIZ];
      int fd;
      int nread;

      testfds = readfds;

      printf("server waiting\n");

      result = select(nfds, &testfds, (fd_set *)0, (fd_set *)0, (struct timeval *)0);
      if (result <1)
      {
         perror("server");
         return 1;
      }

      for (fd = 0; fd < FD_SETSIZE; fd++)
      {
         if (FD_ISSET(fd, &testfds))
         {
            if (fd == server_sockfd)
            {
               c_data.ci.client_len = sizeof(client_address);
               c_data.ci.client_fd = accept(server_sockfd, 
                     (struct sockaddr *)&client_address, 
                        &(c_data.ci.client_len));
               FD_SET(client_sockfd, &readfds);
               nfds++;

            }
         }
      }
   }
}
