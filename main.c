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


int map_code(char *key){
    long int value = 0;
    int i;
    for(i = 0; i < strlen(key); i++){
        value = value * 1 + key[i];
    }
    return value % 2000;
}

Mapa *crear_mapa(void){
    Mapa *mapa =  malloc(sizeof(Mapa));
    mapa->entradas = malloc(sizeof(Entrada*) * 4000);
    for(int i = 0; i<4000; ++i){
        mapa->entradas[i] = NULL;
    }
    return mapa;
}

void mapper(struct stat *sb ,char *file_in_memory, Mapa *mapa){
    char* str = malloc(20);
    
    for(int i = 0; i<sb->st_size; i++){ 
        if((file_in_memory[i] >= 'a' && file_in_memory[i] <= 'z') || (file_in_memory[i] >= 'A' && file_in_memory[i] <= 'Z')){
            strncat(str, &file_in_memory[i],1); 
        }else{ 
            Entrada *entrada = (Entrada *) malloc(sizeof(Entrada));
            entrada->key = str;
            int code = map_code(str);
            if(mapa->entradas[code] == NULL){
                entrada->value = 1;
                mapa->entradas[code] = entrada;
            }else{
                mapa->entradas[code]->value++;
            }
            
            //printf("El str es %s con Codigo %d\n", entrada->key, code);
            memset(str,0,strlen(str)); 
        }
    }
}


void busca(Mapa *mapa){
    char* str = "home";
    int code_to_look = map_code(str);
    printf("El code_to_look es %d\n", code_to_look);
    printf("This is the value of Home %d\n", mapa->entradas[code_to_look]->value);

}


int main(int argc, const char* argv[]){
    Mapa * mapa = crear_mapa();
    int f_map = open("./Files/home.txt", O_RDONLY, S_IRUSR | S_IWUSR);
    if (fstat(f_map, &sb) == -1)
        perror("Error en size ");
    printf("El tamaño del archivo es: %lld\n", sb.st_size);
    //Guardamos en un apuntador el archivo
    char *file_in_memory = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, f_map, 0);
    mapper(&sb, file_in_memory, mapa);
    busca(mapa);
    //IMPRIMIR TODO EL FILE EN LA CONSOLA:

    printf("\n");//*/
    munmap(file_in_memory, sb.st_size);
    close(f_map);

    return 0;


}