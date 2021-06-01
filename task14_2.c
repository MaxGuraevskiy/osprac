#include <signal.h>
#include <stdio.h>

void my_handler(int nsig) {
  if (nsig == 2)
     printf("Received %d, CTRL+C\n", nsig);
  else if (nsig == 3)
     printf("Received %d, CTRL+4\n", nsig);
}

int main(void) {
  (void)signal(SIGINT, my_handler);
  (void)signal(SIGQUIT, my_handler);
  while(1);
  return 0;
}
