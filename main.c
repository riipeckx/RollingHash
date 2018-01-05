#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

char* loadFile (char* given_file, int* p_size) {
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
        printf("The file is correct.\nIt contains %d characters.\n", *p_size);

        read(fd, allocatedMemory, *p_size);
        close(fd);

        return allocatedMemory;
    };
}

void quit (void){
    int i;
    printf("Press any key to continue...");
    read(0, &i, 1);
};

int main (void) {
    // Variables
    char *buffer;
    int size;
    int i;
    int csum;
    int remove[256];
    int N;
    char **P;

    // Pre-Calculating
    for (i=0; i<256;i++){
        remove[i] = 33 * 33 * i;
    }


     // Load File
     buffer = loadFile("/home/riipeckx/C/RollingHash/input.txt", &size);


     // Rolling Checksum
    csum = 33 * 33 * buffer[0] + 33 * buffer[1] + buffer[2];
    printf("csum[0] = %d \n", csum);

    for (i = 0; i < size - 3; i++) {
        //csum = csum - 33 * 33 * buffer[i];
        csum = csum - remove[buffer[i]];
        csum = csum * 33;
        csum = csum + buffer[i + 3];
        printf("csum[%d] = %d \n", i + 1, csum);
    }


    /*Dynamic Hash Table
    /*int hashTable[8];

    for(int i = 0; i<hashTable; i++){
        hashTable[i] = -1;
        printf("%d \n", hashTable[]);
    //}*/

    quit();
    return 0;
}
