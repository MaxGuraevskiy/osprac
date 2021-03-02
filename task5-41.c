#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int fd, result;
    size_t size;
    char resstring[14];
    char name[] = "my.fifo";
    (void)umask(0);

    printf("my.fifo is created\n");
    printf("Reading data from fifo\n");

    if ((fd = open(name, O_RDONLY)) < 0) {
        printf("Can\'t open my.fifo for reading\n");
        exit(-1);
    }

    size = read(fd, resstring, 14);
    if (size < 0) {
        printf("Can\'t read string\n");
        exit(-1);
    }
    printf("Read from fifo: %s\n", resstring);
    printf("Reader exit\n");
    close(fd);
    return 0;
}
