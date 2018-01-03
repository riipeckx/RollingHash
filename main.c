#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
    int fd;
    int i;

    fd = open("c:/input.txt", O_RDONLY, 0666);
    i = lseek(fd, 0, SEEK_END);
    close(fd);

//Input file verification method
    if (i==-1){
        printf("The file isn't correct\n");
        printf("err = %s\n", strerror(errno));
    }
    else{
        printf("size = %d\n", i);
    }

    return 0;
}