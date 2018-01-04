#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * malloc = Allouer de l'espace mémoire
 * free = Désallouer de l'espace mémoire
 */

//variables declaration
int fd;
int size;
char* allocatedMemory = NULL;
char textInBuffer = 0;

void fileOpening(){
    fd = open("c:/input.txt", O_RDONLY, 0666);
};

void fileSize(){
    size = lseek(fd, 0, SEEK_END);
};

void memoryAllocation(){
    lseek(fd, 0, SEEK_SET);
    allocatedMemory = malloc(size);
    printf("Allocated memory = %p (%d)\n", allocatedMemory, size);
};

void memoryDeallocation(){
    free(allocatedMemory);
};

void fileVerification(){
    if (size == -1) {
        printf("The file isn't correct\n");
        printf("err = %s\n", strerror(errno));
    } else {
        printf("The file contains %d characters.\n", size);
    }
};

int main(void) {

    fileOpening();
    fileSize();

    memoryAllocation();

    fileVerification();

    memoryDeallocation();
    return 0;
}