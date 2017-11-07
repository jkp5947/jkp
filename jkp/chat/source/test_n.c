#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
   /*
   char Buf[1024]={0};
   char buf[1024] = "abcdefghijklmnopqrstuvwxyz";
   int a = 1;
   int num;

   
   sprintf(Buf, "%d|%s", a, buf);
   printf("BUF = %s\n",Buf);
   sscanf(Buf, "%d|%[^\n]", &num, buf);
   printf("num = %d\n",num);
   printf("str = %s\n",buf);
   */

   char buf1[10]={0};
   char buf2[10]={0};
   char *ptr;
   int i=0;
   ptr = "abcdefg";
   
   strncpy(buf1, ptr, sizeof(ptr));
   memcpy(buf2, ptr, sizeof(ptr));

   printf("strcpy %s\n",buf1);
   printf("memcpy %s\n",buf2);

   while(i != 10)
   {
      printf("%c",buf1[i++]);
   }
   printf("\n");
   i=0;

   while(i != 10)
   {
      printf("%c",buf2[i++]);
   }
   printf("\n");
   return 0;
}
