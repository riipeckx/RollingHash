#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

uint8_t * loadFile (char* given_file, int* p_size) {
    int fd;
    uint8_t *allocatedMemory = NULL;

    fd = open(given_file, O_RDONLY, 0666);
    *p_size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    allocatedMemory = malloc(*p_size);

    if (*p_size == -1) {
        printf("The file isn't correct\n");
        printf("Error code is = %s\n", strerror(errno));
    } else {
        printf("The file is correct.\nIt contains %d characters.\n", *p_size);

        read(fd, allocatedMemory, *p_size);
        close(fd);

        return allocatedMemory;
    };
};



void quit (void){
    int i;
    printf("Press any key to continue...");
    read(0, &i, 1);
};

int main (void) {
    // Variables
    uint8_t *buffer;
    int size;
    int i;
    int csum;
    int remove[256];
    int a = csum;

    // Clock
    clock_t start, stop;

    start = clock();


    // Pre-Calculating
    for (i=0; i<256;i++){
        remove[i] = 33 * 33 * i;
    }


     // Load File
    buffer = loadFile("/home/riipeckx/C/RollingHash/a.out", &size);



     // Rolling Checksum
    csum = 33 * 33 * buffer[0] + 33 * buffer[1] + buffer[2];
    //printf("csum[0] = %d \n", csum);

    for (i = 0; i < size - 3; i++) {
        csum = csum - remove[buffer[i]];
        csum = csum * 33;
        csum = csum + buffer[i + 3];
        //printf("csum[%d] = [%d] %d\n", i+1,  (int)buffer[i], csum);
        printf("0x%X \n", csum);
    }

    stop = clock();

    printf("time = %f\n", (double)(stop - start) / CLOCKS_PER_SEC);


    quit();
    return 0;
};
