#include "chat_server.h"

int recv_id(jkp_global *g_data, char *id, Client_data *save)
{
   int find_fd;
   long ofs;

   ofs = OFFSET(Client_data, ci.client_id);
   find_fd = linkedlist_search(&(g_data->c_list), id, ofs, sizeof(id));
   if (find_fd == -1)
   {
      strncpy(save->ci.client_id, id, 10);
     // linkedlist_add(&(g_data->c_list), save, 0);
      return 0;
   }
   else 
      return -1;
}

void send_list(jkp_global *g_data, int request_fd)
{
   Node *eye;
   eye = g_data->c_list.head->next;

   if (eye != 0)
   {
      while (eye != g_data->c_list.tail)
      {
         write(request_fd,eye,sizeof(eye));    
         eye = eye->next;
      }
   }
   else
   {
      write(request_fd,"Nolist\n",sizeof("Nolist\n"));
   }
   return ;
}

void send_inv(jkp_global *g_data, int inv_fd, int request_fd)
{
   Node *eye;
   char id[10]={0};
   char buf[BUFSIZ]={0};
   eye = g_data->c_list.head->next;

   while (eye != g_data->c_list.tail)
   {
      if (memcmp((char *)(eye->pData), &request_fd, 4) == 0)
      {
         memcpy(id, &(((Client_data *)eye->pData)->ci.client_fd), 10); 
         break;
      }
      eye = eye->next;
   }
   sprintf(buf, "[%s]님이 초대하셨습니다. 수락하시겠습니까? (Y/N)",id);
   write(inv_fd, buf, sizeof(buf));
}

void call_history(jkp_global *g_data, int request_fd)
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
   int result;
   int cnt = 0;
   int nfds = 4;
   Room r_data;
   Client_data c_data;
   fd_set readfds, testfds;
   
   linkedlist_init(&(global_data.c_list));
   linkedlist_init(&(global_data.h_list));
   linkedlist_init(&(global_data.r_list));
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
      int recv_flag;
      int inv_fd=0;
      int reply_flag; 
      testfds = readfds;

      printf("server waiting\n");

      result = select(nfds, &testfds, (fd_set *)0, 
            (fd_set *)0, (struct timeval *)0);
      if (result <1)
      {
         perror("server");
         return 1;
      }

      for (fd = 0; fd < nfds; fd++)
      {
         if (FD_ISSET(fd, &testfds))
         {
            if (fd == server_sockfd)
            {
               c_data.ci.client_len = sizeof(c_data.ci.client_address);
               c_data.ci.client_fd = accept(server_sockfd, 
                     (struct sockaddr *)&(c_data.ci.client_address), 
                        &(c_data.ci.client_len));
               FD_SET(c_data.ci.client_fd, &readfds);
               nfds++;
              // send_list(&global_data, c_data.ci.client_fd);
            }
            else
            {
               read(fd, buf, sizeof(buf));
               sscanf(buf, "%d|%[^\n]", &recv_flag, buf);
               switch (recv_flag)
               {
                  case 0:
                     
                  case 1:
                     reply_flag = recv_id(&global_data, buf, &c_data);
                     if (reply_flag == -1)
                        write(fd, "Duplicate user!", sizeof("Duplicate user!"));
                     break;
                  case 2: 
                    // send_list(&global_data, request_fd);
                     break;
                  case 3: 
                     r_data.att_fd[1] = linkedlist_search(&(global_data.c_list), buf, 0,4);
                     if (r_data.att_fd[1] == -1)
                        write(fd, "No User", sizeof("No User"));
                     else
                     {
                        r_data.att_fd[0] = fd;
                        send_inv(&global_data, inv_fd, fd);                
                     }
                     break;
                  case 4:
                     reply_flag = strncmp(buf, "수락", sizeof("수락"));
                     if (reply_flag == 0) //수락시
                     {
                        
                     }
                     else 
                     {
                     
                     }
                     break;
                  case 5:
                     call_history(&global_data, fd);
                     break;
                  case 6:
                     exit_client(&global_data, fd);

               }
            }
         }
      }
   }
} 
