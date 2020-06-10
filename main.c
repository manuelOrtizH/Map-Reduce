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
struct stat sb;

void mapper(struct stat *sb ,char *file_in_memory){
    Map *mapper;
    int inicio = 0;
    int final;
    char* str = malloc(20); //Se inicializa un nuevo string, el cual será la key
    Map map; //Se inicializa el mapa en general. Necesitamos un solo mapa por cada llamada a este método
    for(int i = 0; i<sb->st_size; i++){ //sb->st_size es igual al tamaño de todo el archivo
        if((file_in_memory[i] >= 'a' && file_in_memory[i] <= 'z') || (file_in_memory[i] >= 'A' && file_in_memory[i] <= 'Z')){
            //En el if se asegura que sean letras y no comas, apóstrofes, o cualquier otro símbolo que no sea letra
            strncat(str, &file_in_memory[i],1); //Le voy pegando al string un nuevo caracter
        }else{ //Cuando encuentre un espacio, coma, apóstrofe, etc, etc, deja de pegarle caracteres al string
            Entrada entrada_nueva; //Se crea una struct Entrada, la cual será una nueva entrada
            entrada_nueva.key = str; //Se asigna el string completo al key de la struct Entrada
            printf("The string to add to the map is: %s\n", entrada_nueva.key);
            entrada_nueva.value = 1;
            map.entradas = &entrada_nueva; //Se asigna una entrada struct nueva a la Struct Mapa
            memset(str,0,strlen(str)); //Se resetea el string para que no se le agregue cosas al string pasado
            
        }
        
    }

    
}





int main(int argc, const char* argv[]){
    int f_map = open("./Files/home.txt", O_RDONLY, S_IRUSR | S_IWUSR);
    if (fstat(f_map, &sb) == -1)
        perror("Error en size ");
    printf("El tamaño del archivo es: %lld\n", sb.st_size);
    //Guardamos en un apuntador el archivo
    char *file_in_memory = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, f_map, 0);
    mapper(&sb, file_in_memory);
    //IMPRIMIR TODO EL FILE EN LA CONSOLA:

    printf("\n");//*/
    munmap(file_in_memory, sb.st_size);
    close(f_map);

    return 0;


}