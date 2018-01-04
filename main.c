#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

char* loadFile(char* given_file, int* p_size){

    int fd;
    char* allocatedMemory = NULL;

    fd = open(given_file, O_RDONLY, 0666);
    *p_size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    allocatedMemory = malloc(*p_size);
    printf("Allocated memory = %p (%d)\n", allocatedMemory, *p_size);
    read(fd, allocatedMemory, *p_size);
    close(fd);

    return allocatedMemory;
};

int main(void) {
    char* buffer;
    int size;
    int i;

    buffer = loadFile("c:/input.txt", &size);
    printf("%d\n",size);
    for(i=0;i<size;i++){
        printf("%c", buffer[i]);
    }
    return 0;
}