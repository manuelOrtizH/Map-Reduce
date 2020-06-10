typedef struct KeyValue{
    char* key; //El string
    int value; //Num de repeticiones en el texto (Siempre será uno)
    
} Entrada;

typedef struct Mapa{
    Entrada **entradas;
} Mapa;


