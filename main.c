#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#define HSIZE 16

uint8_t * loadFile (char* given_file, int* p_size){
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
    char path;
    uint8_t *buffer;
    int size;
    int i, j;
    int csum;
    int remove[256];
    int a = csum;
    int *hashTable;

    // hashTable
    hashTable = (int *)malloc(HSIZE * sizeof(int));
    memset(hashTable, -1, HSIZE * sizeof(int));

    // Clock
    clock_t start, stop;

    start = clock();

    // Pre-Calculating
    for (i=0; i<256;i++){
        remove[i] = 33 * 33 * i;
    }

     // Load File
    buffer = loadFile("1GB.zip", &size);

     // Rolling Checksum
    csum = 33 * 33 * buffer[0] + 33 * buffer[1] + buffer[2];
    //printf("csum[0] = %d \n", csum);

    for (i = 0; i < size - 3; i++) {

        //printf("#%-8d ", i);
        //for (j=0; j<HSIZE; j++) printf(" %3d", hashTable[j]);
        //printf(" | %3d (%c%c%c)\n", csum % HSIZE, buffer[i], buffer[i+1], buffer[i+2]);

        hashTable[csum % HSIZE] = i;

        //int csum_hex;
        csum = csum - remove[buffer[i]];
        csum = csum * 33;
        csum = csum + buffer[i + 3];
    }
    stop = clock();

    printf("time = %f\n", (double)(stop - start) / CLOCKS_PER_SEC);

    for (i=0; i<HSIZE; i++) printf("%d ", hashTable[i]);
    printf("\n");


    /*printf("sizeof char = %d\n", sizeof(char));
    printf("sizeof int = %d\n", sizeof(int));
    printf("sizeof long int = %d\n", sizeof(long int));
    printf("sizeof long long int = %d\n", sizeof(long long int));
    printf("sizeof short int = %d\n", sizeof(short int));*/

    //for (i=0; i<8; i++) hashTable[i]= -1;



    //quit();
    return 0;

};
