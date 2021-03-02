  
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {

    int fd[2];
    size_t size = 1;
    char* resstring = malloc(1 * sizeof(char));

    if(pipe(fd) < 0) {
        printf("Can\'t create pipe\n");
        exit(-1);
    }
    fcntl(fd[1], F_SETFL, fcntl(fd[1], F_GETFL) | O_NONBLOCK);

    int result = 0;
    for (;size == 1;++result)
        size = write(fd[1], resstring, 1);

    printf("You wrote %d bytes\n", result);
    return 0;
}
