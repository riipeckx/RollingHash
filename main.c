#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

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
    /* Variables */
    char* buffer;
    int size;
    int i;

    /* Buffer */
    buffer = loadFile("c:/input.txt", &size);
    printf("%d\n",size);
    for(i=0;i<size-2;i++){
        int csum = 33*33*buffer[i] + 33*buffer[i+1] + buffer[i+2];
        printf("%d %c,%c,%c %d \n ", i, buffer[i], buffer[i+1], buffer[i+2], csum);
    }

    return 0;
}