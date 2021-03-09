#include <sys/types.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
int main()
{
    int shmid;
    char pathname[] = "task7_writer.c";
    key_t key;
    char *source_code;
    
    // Я не знаю почему, но ключ меньше нуля
    key = ftok(pathname, 0);

    // Выделение памяти   
    if ((shmid = shmget(key, 5000 * sizeof(char), 0666 | IPC_CREAT | IPC_EXCL)) < 0) {

        if (errno != EEXIST) { 
        printf("Can\'t create shared memory\n"); 
        exit(-1); 

        } else { 
        if ((shmid = shmget(key, 5000 * sizeof(char), 0)) < 0) { 
        printf("Can't find shared memory\n"); 
        exit(-1); 
        } 

        }
    }
    source_code = shmat(shmid, NULL, 0);
   
    FILE *file = fopen(pathname, "r");
    char ch;
    if(file == NULL){
    printf("ouch\n"); 
    exit(-1); 
    }

    // Запись файла
    int i = 0;
    while ((ch = fgetc(file)) != EOF) 
    { 
        source_code[i] = ch; 
        i++; 
    }
    fclose(file);

    if (shmdt(source_code) < 0) {
        printf("Can't detach shared memory\n");
        exit(-1);
    }
    return 0;
}
