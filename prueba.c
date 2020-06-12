#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include "map.h"
#define BUZZ_SIZE 1024

int main(int argc, const char* argv[]){
    int c;
    FILE *file;

    file = fopen("./Files/home.txt", "r");
    if (file) {
    while ((c = getc(file)) != EOF)
        //putchar(c);
        printf("%c", c);
    fclose(file);
}

}