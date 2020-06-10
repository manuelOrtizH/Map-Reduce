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
char *file_in_memory;

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
    for(int i = 0; i<sb.st_size/3; i++){
        mapa->entradas[i] = NULL;
    }
    return mapa;
}

Mapa* mapper(int from, int to){
    int counter = 0;
    char* str = malloc(30);
    Mapa * mapa = crear_mapa();
    for(int i = from; i<=to; i++){ 
        if((file_in_memory[i] >= 'a' && file_in_memory[i] <= 'z') || (file_in_memory[i] >= 'A' && file_in_memory[i] <= 'Z') ){
            strncat(str, &file_in_memory[i],1); 
        }else{ 
            Entrada *entrada = (Entrada *) malloc(sizeof(Entrada));
            strcpy(entrada->key, str);
            entrada->value = 1;
            mapa->entradas[counter] = entrada;
            counter++;
            memset(str,0,strlen(str)); 
        }
    }
    mapa->counterWords = counter;
    return mapa;
}

void busca(Mapa *mapa){
    
    for(int i = 0; i<mapa->counterWords; i++){
        printf("The key of this map is: %s   .The value of the string is: %d\n", mapa->entradas[i]->key, mapa->entradas[i]->value);
    }

}



int main(int argc, const char* argv[]){
    Mapa *mapa1 = NULL;
    Mapa *mapa2 = NULL;
    Mapa *mapa3 = NULL;
    int f_map = open("./Files/home.txt", O_RDONLY, S_IRUSR | S_IWUSR);
    if (fstat(f_map, &sb) == -1)
        perror("Error en size ");
    printf("El tamaño del archivo es: %lld\n", sb.st_size);
    
    //Guardamos en un apuntador el archivo
    file_in_memory = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, f_map, 0);
    pid_t p1, p2, p3;
    /*if((p1=fork())== 0){
       mapa1 = mapper(0, sb.st_size/3);
       sleep(1);
    }else if((p2=fork())==0){
       mapa2 = mapper(sb.st_size/3, sb.st_size/3+sb.st_size/3);
       sleep(1);
    }else if((p3=fork())==0){
       mapa3 = mapper(sb.st_size/3+sb.st_size/3, sb.st_size);
       sleep(1);
    }*/
    //TODO ESTO DEBE PASAR DE FORMA SIMULTÁNEA
    mapa1 = mapper(0, sb.st_size/3);
    //filter(mapa1); Ir agregando cada string a la struct nueva, donde se usará un hash_code igual
    //mapa2 = mapper(sb.st_size/3, sb.st_size/3+sb.st_size/3);
    //filter(mapa2); Ir agregando cada string a la struct nueva, donde se usará un hash_code igual
    //mapa3 = mapper(sb.st_size/3+sb.st_size/3, sb.st_size);
    //filter(mapa3); Ir agregando cada string a la struct nueva, donde se usará un hash_code igual
    busca(mapa1);
    
    int status;
    /*waitpid(p1, &status, 0);
    waitpid(p2, &status, 0);
    waitpid(p3, &status, 0);
    */
    
    
    
    //IMPRIMIR TODO EL FILE EN LA CONSOLA:

    printf("\n");//*/
    munmap(file_in_memory, sb.st_size);
    close(f_map);

    return 0;


}