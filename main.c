#include <stdio.h>
#include <fcntl.h>

int main()
{
    int fd;
    int i;

    fd = open("input.txt", O_RDONLY, 0);
    i = lseek(fd, 0, SEEK_END);
    close(fd);

    if (i=-1)
        printf("The file isn't correct\n");
    else
        printf("size = %d\n", i);
    return 0;
}