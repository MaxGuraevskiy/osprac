#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    FILE *file;
    char l[3], next[3];
    int i = 0;

    file = fopen("BBW", "w");

    symlink("BBW", "0");

    sprintf(l, "%d", i);

    fclose(file);

    while ((file = fopen(l, "w")) != NULL)
    {
        sprintf(l, "%d", i);
        sprintf(next, "%d", ++i);
        symlink(l, next);
        sprintf(l, "%d", i);
        fclose(file);
    }
    
    printf("Result - %d", i);
}
