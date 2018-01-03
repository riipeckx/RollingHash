#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

/*
 * malloc = Allouer de l'espace mémoire
 * free = Désallouer de l'espace mémoire
 */

int main(void) {
    int fd;
    int size;
    char* allocatedMemory = NULL;

    fd = open("c:/input.txt", O_RDONLY, 0666);
    size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    allocatedMemory = malloc(size);
    printf("Allocated memory = %p (%d)\n", allocatedMemory, size);

//Input file verification method
    if (size == -1) {
        printf("The file isn't correct\n");
        printf("err = %s\n", strerror(errno));
    } else {
        printf("The file contains %d characters.\n", size);
    }

    free(allocatedMemory);
    return 0;
}