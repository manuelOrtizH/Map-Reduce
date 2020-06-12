typedef struct KeyValue{
    char key[30]; //El string
    long int value; //Num de repeticiones en el texto (Siempre será uno)
} Entrada;

typedef struct Mapa{
    Entrada **entradas;
    long counterWords;
    long total;
} Mapa;




