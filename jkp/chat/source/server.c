#include "chat_server.h"



int main(void)
{
   int server_sockfd;
   int server_len;
   struct sockaddr_in server_address;
   struct sockaddr_in client_address;
   int nfds = 4;
   int chk,result;
   fd_set readfds, testfds;

   Client_data c_data;

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
      testfds = readfds;

      printf("server waiting\n");
      result = select(nfds, &testfds, (fd_set *)0,(fd_set *)0, (struct timeval *)0);
      
      if (result < 1)
      {
         perror("server");
         return 1;
      }   
      for (chk = 0; chk < FD_SETSIZE; chk++)
      {
         if (FD_ISSET(chk, &testfds))
         {
            if(chk == server_sockfd)
            {
               c_data.ci.client_len = sizeof(client_address);
               c_data.ci.client_fd = accept(server_sockfd, 
                     (struct sockaddr *)&client_address, &c_data.ci.client_len);
               FD_SET(c_data.ci.client_fd, &readfds);
               nfds++;
            }
         }
      }
   }
}

//recv한 클라이언트 대화명을 리스트에 추가하고
//Server화면에 입장 메시지를 출력.
void recv_id(jkp_global *global_data, char *recv_id)
{

}
//클라이언트에서 접속자 목록 요청시 클라이언트 데이터를 가지고있는
//linked list에서 대화명들을 요청한 클라이언트 fd를 통하여 전송.
void send_list(jkp_global *global_data, int request_fd)
{

}
//클라이언트로 부터 초대 요청시 일치하는 대화명이 있는지 확인후
//일치하는 접속자가 있으면 그 클라이언트의 fd를 리턴한다.
int inv_request(jkp_global *global_data, char *id)
{

}
//찾은 접속자에게 초대를 보냄
void send_inv(jkp_global *global_data, int inv_fd)
{

}
//요청한 fd를 통해 대화내용을 불러들이고 대화내용을 send
void call_history(jkp_global *global_data, int request_fd)
{

}
//종료 메시지 수신시 해당 fd를 받아와 클라이언트 정보를 삭제
//클라이언트의 퇴장을 출력한다.
void exit_client(jkp_global *global_data, int exit_client_fd)
{

}
