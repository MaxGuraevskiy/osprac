#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <errno.h> 
#include <stdlib.h> 

int main() 
{ 
    char *string; 
    int shmid; 
    key_t key;

    char path[] = "task7_writer.c"; 

    key = ftok(path, 0); 
    shmid = shmget(key, 5000 * sizeof(char), 0); 

    if(shmid < 0){ 
        printf("Can\'t found shared memory\n"); 
        exit(-1); 
    } 
    string = shmat(shmid, NULL, 0); 
    printf("%s\n", string); 

    shmdt(string); 
    shmctl(shmid, IPC_RMID, 0); 

    return 0; 
}
