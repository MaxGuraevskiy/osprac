
#include <stdio.h>
int main(int argc, char *argv[], char *envp[])
{
   for (int i = 0; i < argc; i++)
   {
      printf("%s\n", argv[i]);
   }

   printf("envp:\n");
   int j = 0;
   while(envp[j] != NULL)
   {
     printf("%s\n", envp[j]);
     j++;
   }

   return 0;   
 }