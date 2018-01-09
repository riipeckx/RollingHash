#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#define HSIZE 16
#define MUL 62

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

int lSeq (char *sequence, int size, int i, int j){
    if (i>=size || j>=size || sequence[i]!=sequence[j]) return 0;
    return 1 + lSeq(sequence, size, i+1, j+1);
}

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
        remove[i] = MUL * MUL * i;
    }

     // Load File
    //buffer = loadFile("input.txt", &size);
    //buffer = loadFile("5MB.zip", &size);
    buffer = loadFile("1GB.zip", &size);

     // Rolling Checksum
    csum = MUL * MUL * buffer[0] + MUL * buffer[1] + buffer[2];

    for (i = 0; i < size - 3; i++) {

        //printf("%-5d", i);
        //for (j = 0; j<HSIZE; j++) printf("%3d", hashTable[j]);
        //printf(" | %3d (%c%c%c)", csum % HSIZE, buffer[i], buffer[i+1], buffer[i+2]);
        //printf(" %d\n", lSeq(buffer, size, hashTable[csum % HSIZE], i));

        hashTable[csum % HSIZE] = i;

        csum -= remove[buffer[i]];
        csum *= MUL;
        csum += buffer[i + 3];
    }

    stop = clock();

    printf("time = %f\n", (double)(stop - start) / CLOCKS_PER_SEC);

    for (i=0; i<HSIZE; i++) printf("%d ", hashTable[i]);
    printf("\n");

    quit();
    return 0;
}
