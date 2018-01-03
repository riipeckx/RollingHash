#include <stdio.h>
#include <fcntl.h>


int main()
{
    int fd;
    int i;

    fd = _open("input.txt", O_RDONLY, 0);

    i = _seek(fd, 0, SEEK_END);
    printf("size = %d\n", i);

    _close(fd);
    return 0;
}