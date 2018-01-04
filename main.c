#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * malloc = Allouer de l'espace mémoire
 * free = Désallouer de l'espace mémoire
 */

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


    /*
    if (size == -1) {
        printf("The file isn't correct\n");
        printf("err = %s\n", strerror(errno));
    } else {
        printf("The file contains %d characters.\n", size);
    }*/

    //close

    return allocatedMemory;
};

int main(void) {
    char* buffer;
    int size;
    int i = 0;

//Input file verification method
    buffer = loadFile("c:/input.txt", &size);

    printf("%d\n",size);
    return 0;
}