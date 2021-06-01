#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>
#include <stdlib.h>

int getBit(int num, int bitPos)
{
    return num & (1 << bitPos) ? 1 : 0;
}
int getSignal(int num, int bitPos)
{
    return getBit(num, bitPos) ? SIGUSR1 : SIGUSR2;
}

int number = 0;
int position = 0;
pid_t transmitter_pid;
pid_t receiver_pid;

void my_handler(int nsig)
{
    printf("signal=%d\n", nsig == SIGUSR1 ? 1 : 0);

    if (nsig == SIGUSR2)
    {
        printf("number %d transmitted\n", number);
        exit(0);
    }

    if (position >= sizeof(int) * 8)
    {
        printf("number %d transmitted\n", number);
        exit(0);
    }
    kill(receiver_pid, getSignal(number, position++));
}

int main(void)
{
    (void)signal(SIGUSR1, my_handler);
    (void)signal(SIGUSR2, my_handler);

    printf("pid = %d\n", getpid());
    printf("pid = ");
    scanf("%d", &receiver_pid);

    printf("throw me your number: ");
    scanf("%d", &number);

    for (size_t i = 0; i < sizeof(int) * 8; i++)
    {
        printf("%d", getBit(number, i));
    }
    printf("\n");
    if (position >= sizeof(int) * 8)
    {
        printf("number %d transmitted\n", number);
        exit(0);
    }
    kill(receiver_pid, getSignal(number, position++));

    while (1);
    return 0;
}
