typedef struct KeyValue{
    char key[50]; //El string
    int value; //Num de repeticiones en el texto (Siempre será uno)
} Entrada;

typedef struct Mapa{
    Entrada **entradas;
    int counterWords;
} Mapa;




