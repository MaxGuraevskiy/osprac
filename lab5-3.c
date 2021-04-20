#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

// parent
// write
// A(s,2)
// Z(s)
// read

// child
// D(s,1)
// read
// write
// D(s,1)

int main() {
    int fd[2], result;
    struct sembuf mybuf;
    int semid;
    key_t key;
    size_t size;
    char resstring[14];
    int n;
    scanf("%d", &n);

    if ((semid = semget(key, 1, 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
        if ((semid = semget(key, 1, 0)) < 0) {
            printf("Can't find shared memory");
            exit(-1);
        }
    }
    if (pipe(fd) < 0) {
        printf("Can\'t open pipe\n");
        exit(-1);
    }
    result = fork();

    if (result < 0) {
        printf("Can\'t fork child\n");
        exit(-1);
    } else if (result > 0) {

        /* Parent process */
        for (int i = 0; i < n; ++i) {

            size = write(fd[1], "Hello, World!", 14);
            printf("Parent write!\n");

            if (size != 14) {
                printf("Can\'t write all string to pipe\n");
                exit(-1);
            }

            mybuf.sem_op = 2;
            mybuf.sem_flg = 0;
            mybuf.sem_num = 0;
            semop(semid, &mybuf, 1);
            mybuf.sem_op = 0;
            mybuf.sem_flg = 0;
            mybuf.sem_num = 0;
            semop(semid, &mybuf, 1);

            size = read(fd[0], resstring, 14);
            printf("Parent is typing: %s\n", resstring);
        }

        if (close(fd[0]) < 0) {
            printf("parent: Can\'t close reading side of pipe\n");
            exit(-1);
        }
        if (close(fd[1]) < 0) {
            printf("parent: Can\'t close writing side of pipe\n");
            exit(-1);
        }

        printf("Parent exit\n");
    } else {

/* Child process */
        for (int i = 0; i < n; ++i) {
            mybuf.sem_op = -1;
            mybuf.sem_flg = 0;
            mybuf.sem_num = 0;
            semop(semid, &mybuf, 1);

            size = read(fd[0], resstring, 14);
            printf("Child is typing: %s\n", resstring);

            if (size < 0) {
                printf("Can\'t read string from pipe\n");
                exit(-1);
            }

            size = write(fd[1], "Hello, World!", 14);
            printf("Child write!\n");

            mybuf.sem_op = -1;
            mybuf.sem_flg = 0;
            mybuf.sem_num = 0;
            semop(semid, &mybuf, 1);
        }

        if (close(fd[1]) < 0) {
            printf("child: Can\'t close writing side of pipe\n");
            exit(-1);
        }
        if (close(fd[0]) < 0) {
            printf("child: Can\'t close reading side of pipe\n");
            exit(-1);
        }
    }
    return 0;
}
