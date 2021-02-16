#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int     fd[2], fd2[2], result;
    
    size_t size;
    char  resstring[14];
    
    if (pipe(fd) < 0) {
        printf("Can\'t open pipe\n");
        exit(-1);
    }
    
    if (pipe(fd2) < 0) {
        printf("Can\'t open pipe\n");
        exit(-1);
    }
    
    result = fork();
    
    if (result < 0) {
        printf("Can\'t fork child\n");
        exit(-1);
    } else if (result > 0) {
        close(fd[0]);
        
        close(fd2[1]);
        
        size = write(fd[1], "Hello, anime!", 14);
        
        size = read(fd2[0], resstring, 14);
        
        if (size != 14) {
            printf("Can\'t write all string to pipe\n");
            exit(-1);
        }
        
        printf("Parent exit, resstring: %s", resstring);
        
        close(fd[1]);
        
        
        close(fd2[0]);
        
        
        printf("Parent exit\n");
        
    } else
    {
        close(fd[1]);
        close(fd2[0]);
              
        size = write(fd2[1], "Hello, world!", 14);
        size = read(fd[0], resstring, 14);
              
        printf("Child exit, resstring: %s\n", resstring);
              
        close(fd[0]);
        close(fd2[1]);
    }
return 0;
}
