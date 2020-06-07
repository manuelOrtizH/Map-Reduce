#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>


int main(int argc, const char* argv[]){
    int f_map = open("./Files/alice.txt", O_RDONLY, S_IRUSR | S_IWUSR);
    struct stat sb;
    if (fstat(f_map, &sb) == -1)
        perror("Error en size ");
    printf("El tamaño del archivo es: %lld\n", sb.st_size);
    //Guardamos en un apuntador el archivo
    char *file_in_memory = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, f_map, 0);

    /* IMPRIMIR TODO EL FILE EN LA CONSOLA:
    for(int i = 0; i<sb.st_size; i++){
        printf("%c", file_in_memory[i]);
    }
    printf("\n");*/
    munmap(file_in_memory, sb.st_size);
    close(f_map);

    return 0;
}