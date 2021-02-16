#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    int     fd;
    size_t  size;
    (void)umask(0);
    
    if ((fd = open("myfile", O_WRONLY)) < 0) {
        printf("Can\'t open file\n");
        exit(-1);
    }
    size = write(fd, "Hello, world!", 14);
    close(fd);
    
    char string[14];
    if ((fd = open("myfile", O_RDONLY)) < 0) {
        printf("Can\'t open file\n");
        exit(-1);
    }
    size = read(fd, string, 14);
    close(fd);
    printf("%s\n\r", string);
    return 0;
}
