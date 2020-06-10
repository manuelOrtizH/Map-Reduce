typedef struct KeyValue{
    char* key; //El string
    int value; //Num de repeticiones en el texto (Siempre será uno)
} KeyValue;

typedef struct Map{
    KeyValue **entradas;
} Map;


