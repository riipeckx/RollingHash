#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

char* loadFile(char* given_file, int* p_size) {
    int fd;
    char *allocatedMemory = NULL;

    fd = open(given_file, O_RDONLY, 0666);
    *p_size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    allocatedMemory = malloc(*p_size);

    if (*p_size == -1) {
        printf("The file isn't correct\n");
        printf("Error code is = %s\n", strerror(errno));
    } else {
        printf("The file contains %d characters.\n", *p_size);

        read(fd, allocatedMemory, *p_size);
        close(fd);

        return allocatedMemory;
    };
}

int quit(){
    int i;
    printf("Press any key to continue...");
    read(0, &i, 1);
};

int main(void) {
    /* Variables */
    char *buffer;
    int size;
    int i;
    int csum;

    /* Load File */
    buffer = loadFile("c:/input.txt", &size);

    /* Rolling Checksum */
    csum = 33 * 33 * buffer[0] + 33 * buffer[1] + buffer[2];
    printf("csum[0] = %d \n", csum);

    for (i = 0; i < size - 3; i++) {
        csum = csum - 33 * 33 * buffer[i];
        csum = csum * 33;
        csum = csum + buffer[i + 3];
        printf("csum[%d] = %d \n", i + 1, csum);
    }

    quit();
    return 0;
}
