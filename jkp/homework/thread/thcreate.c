#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg);

char message[] = "Hello World";

int main()
{
   int res;
   pthread_t a_thread;
   void *thread_result;
   
   res = pthread_create(&a_thread,NULL,thread_function,(void *)message);
   if(res!=0)
   {
      perror("Thread creation failed");
      exit(EXIT_FAILURE);
   }
   printf("Waiting for thread to finish...\n");

   res = pthread_join(a_thread,&thread_result);
   if(res !=0 )
   {
      perror("Thread join failed");
      exit(EXIT_FAILURE);
   }

   printf("thread joined, it returned %s\n",(char *)thread_result);
   exit(EXIT_SUCCESS);

}


void *thread_function(void *arg)
{
   printf("thread_function is running...\nmessage : %s\n",(char *)arg);
   sleep(2);
   pthread_exit("\"exit thread_function\"");
}