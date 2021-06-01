#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>
#include <stdlib.h>

int number = 0;
int position = 0;
pid_t transmitter_pid;
pid_t receiver_pid;

void my_handler(int nsig)
{
    printf("\t%d\n", position, nsig == SIGUSR1 ? 1 : 0, number);
    if (nsig == SIGUSR1) 
        number += (1 << position);
    position++;
    if (position >= 32)
    {
        printf("number %d received\n", number);
        kill(receiver_pid, SIGUSR2);
        exit(0);
    }
    kill(receiver_pid, SIGUSR1);
}

int main(void)
{
    (void)signal(SIGUSR1, my_handler); 
    (void)signal(SIGUSR2, my_handler); 

    printf("pid = %d\n", getpid());
    printf("pid = ");
    scanf("%d", &receiver_pid);

    while (1);
    return 0;
}
