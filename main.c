#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#define MY_BUFFER_SIZE size

int main(void)
{
    int fd;
    int size;
    char mybuffer[size];

    fd = open("c:/input.txt", O_RDONLY, 0666);
    size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    printf("buffer size = %d\n", mybuffer);

//Input file verification method
    if (size==-1){
        printf("The file isn't correct\n");
        printf("err = %s\n", strerror(errno));
    }
    else{
        printf("The file conatins %d caracters.\n", size);
    }

    return 0;
}