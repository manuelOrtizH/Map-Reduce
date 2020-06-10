typedef struct KeyValue{
    char key[30]; //El string
    int value; //Num de repeticiones en el texto (Siempre será uno)
    
} Entrada;

typedef struct Mapa{
    Entrada **entradas;
    int counterWords;
} Mapa;

typedef struct Reduced{
    Entrada **palabras;
} Reduced;


