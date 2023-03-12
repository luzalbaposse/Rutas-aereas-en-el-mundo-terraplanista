#include "airTrip.h"

char* strDup(char* src) {
    /*
    Consigna: duplica un string. Debe contar la cantidad de caracteres totales de src y solicitar la memoria equivalente. Luego, debe compiar todos los caracteres a esta nueva área de memoria. Además como valor de retorno se debe retornar el puntero al nuevo string
    */
    
    if (src == NULL){ // Si el string es NULL, retornamos NULL
        return NULL;
    }
    int len = 0;
    
    // Mientras no lleguemos al final del string
    
    while (src[len] != '\0'){
        // Incrementamos el contador 
        len++; 
    }
    // Reservamos memoria para el nuevo string
    char* dest = (char*) malloc(sizeof(char) * (len + 1)); 
    int i = 0;
    
    // Mientras no lleguemos al final del string
    
    while (src[i] != '\0'){
        // Copiamos el caracter 
        dest[i] = src[i]; 
        i++; 
    }
    
    // Retornamos el puntero al nuevo string
    
    return dest; 
}

int strCmp(char*a, char* b) {
    /*
    Consigna: Compara dos strings en orden lexicográfico. Debe retornar:
    - 0 si son iguales
    - 1 si a < b
    - -1 si a > b
    */
    
    int i = 0; 
    
    // Mientras no lleguemos al final de los strings
    
    while (a[i] != '\0' && b[i] != '\0') {

        // Si el caracter de a es menor que el de b
        if (a[i] < b[i]) { 
            return 1;
        } 
        // Si el caracter de a es mayor que el de b
        else if (a[i] > b[i]) { 
            return -1;
        }
        i++;
    }

    // Si llegamos al final de los strings
    
    if (a[i] == '\0' && b[i] == '\0') { 
        return 0; 
    } 
    
    // Si llegamos al final de a
    
    else if (a[i] == '\0') { 
        return 1; 
    } 
    
    // Si llegamos al final de b
    
    else { 
        return -1; 
    }
}


char* strConcatenate(char* src1, char* src2) {
    /*
    Consigna: La función toma dos strings src1 y src2, y retorna una nueva string que contiene una copia de todos los caracteres de src1 seguidos de los caracteres de src3. Esta función NO libera la memoria de las strings src1 y src2
    */
    if (src1 == NULL || src2 == NULL) { // Si alguno de los strings es NULL, retorna NULL
        return NULL; // Retorna NULL
    }

    int len1 = 0;
    while (src1[len1] != '\0') { // Calcula el largo de src1
        len1++; // Incrementa el contador
    }

    int len2 = 0;
    while (src2[len2] != '\0') { // Calcula el largo de src2
        len2++; // Incrementa el contador
    }

    char* dest = (char*) malloc(sizeof(char) * (len1 + len2 + 1)); // Reserva memoria para la nueva cadena
    if (dest == NULL) { // Si no se pudo reservar memoria, retorna NULL
        return NULL; // Retorna NULL
    }

    int i = 0; // Copia src1 en la nueva cadena
    while (src1[i] != '\0') { // Mientras no lleguemos al final de src1
        dest[i] = src1[i]; // Copiamos el caracter
        i++; // Incrementamos el contador
    }

    int j = 0;
    while (src2[j] != '\0') { // Copia src2 en la nueva cadena
        dest[i] = src2[j];
        i++;
        j++;
    }

    dest[i] = '\0'; // Agrega el caracter nulo al final de la cadena

    return dest;
}


float flyLength(struct airport* a1, struct airport* a2) {
    float deltaLon = a1->longitude - a2->longitude;
    float deltaLat = a1->latitude - a2->latitude;
    return sqrt(deltaLon*deltaLon + deltaLat*deltaLat);
}

struct airTrip* airTripNew(char* plane) {
    struct airTrip* at = (struct airTrip*) malloc(sizeof(struct airTrip));
    at->plane = strDup(plane);
    at->first = 0;
    at->totalLength = 0.0;
    return at;
}

void airTripAddLast(struct airTrip* trip, char* name, float longitude, float latitude) {
    /*
    Consigna: Agrega un nuevo airport al final de la lista de paradas de un trip. 
    Para esto debe recorrer toda la lista hasta encontrar el último lugar donde agregar 
    el nuevo nodo. La nueva estructura de airport debe ser completada con los campos 
    pasados por parámetro.
    */

    struct airport* actual = trip->first; // struct airport* guarda el aeropuerto actual
    while (actual->next != NULL){ // Mientras no sea el último aeropuerto
        actual = actual->next; // Avanzamos al siguiente aeropuerto
    }
    struct airport* nuevo = (struct airport*) malloc(sizeof(struct airport)); // Reservamos memoria para el nuevo aeropuerto
    nuevo->name = strDup(name); // Copiamos el nombre del aeropuerto
    nuevo->longitude = longitude; // Copiamos la longitud del aeropuert o
    nuevo->latitude = latitude; // Copmos la latitud del aeropuerto
    nuevo->next = NULL; // El siguiente aeropuerto es NULL
    trip->totalLength += flyLength(actual, nuevo); // Sumamos la distancia entre el aeropuerto actual y el nuevo

} 

void airTripAddBest(struct airTrip* trip, char* name, float longitude, float latitude) {
/*
Consigna: Escribir una funcion que agrega un nuevo airport en el mejor lugar que se pueda del recorrido. 
Dejando el primer lugar como fijo, se debe buscar el lugar donde agregar la nueva parada que minimice 
el recorrido total, es decir, que agregue la menor cantidad de distancia por tener que pasar por esta 
nueva parada. En los ejemplos a continuación, se puede ver como en el primer caso el mejor lugar para 
agregar la parada es al final, cambiando el último lugar a visitar. En el segundo caso, lo mejor es que 
la nueva parada termine entre las u ́nicas dos paradas de la lista. En el último caso, lo mejor debería 
ser cambiar el primero, pero esto no se permite. Solo se permite buscar el mejor lugar a partir del primero. 
Por lo tanto, esta nueva parada, se termina agregando en el segundo lugar.

*/
    
        struct airport* actual = trip->first; // struct airport* guarda el aeropuerto actual
        struct airport* nuevo = (struct airport*) malloc(sizeof(struct airport)); // struct airport* guarda el nuevo aeropuerto
        nuevo->name = strDup(name); // Aca se copia el nombre del aeropuerto en el nuevo aeropuerto
        nuevo->longitude = longitude; // Aca se copia la longitud del aeropuerto en el nuevo aeropuerto
        nuevo->latitude = latitude; // Aca se copia la latitud del aeropuerto en el nuevo aeropuerto
        nuevo->next = NULL; // Aca se agrega el nuevo aeropuerto al final de la lista de aeropuertos
        float distancia = 0; // float guarda el calculo de la distancia entre dos aeropuertos
        float distanciaMinima = 0; // float guarda la distancia minima entre dos aeropuertos
        struct airport* anterior = NULL; // struct airport* guarda el aeropuerto anterior al nuevo aeropuerto
        struct airport* siguiente = NULL; // struct airport* guarda el aeropuerto siguiente al nuevo aeropuerto
        
        while (actual->next != NULL){ // Mientras el aeropuerto actual no sea el ultimo de la lista
            distancia = flyLength(actual, nuevo) + flyLength(nuevo, actual->next); // Calcula la distancia entre el aeropuerto actual y el nuevo aeropuerto, y la distancia entre el nuevo aeropuerto y el aeropuerto siguiente al actual
            if (distancia < distanciaMinima){ // Si la distancia es menor a la distancia minima
                distanciaMinima = distancia; // La distancia minima pasa a ser la distancia
                anterior = actual; // El aeropuerto anterior al nuevo aeropuerto pasa a ser el aeropuerto actual
                siguiente = actual->next; // El aeropuerto siguiente al nuevo aeropuerto pasa a ser el aeropuerto siguiente al actual
            } // Si la distancia no es menor a la distancia minima, no se hace nada
            actual = actual->next; // El aeropuerto actual pasa a ser el aeropuerto siguiente al actual
        }
        
        if (anterior == NULL){ // Si el aeropuerto anterior al nuevo aeropuerto es NULL
            nuevo->next = trip->first; // El aeropuerto siguiente al nuevo aeropuerto pasa a ser el primer aeropuerto de la lista
            trip->first = nuevo; // El primer aeropuerto de la lista pasa a ser el nuevo aeropuerto
        } else { // Si el aeropuerto anterior al nuevo aeropuerto no es NULL
            nuevo->next = siguiente; // El aeropuerto siguiente al nuevo aeropuerto pasa a ser el aeropuerto siguiente al anterior
            anterior->next = nuevo; // El aeropuerto siguiente al anterior pasa a ser el nuevo aeropuerto
        } 
        
        trip->totalLength += distanciaMinima; // La longitud total del viaje pasa a ser la longitud total del viaje mas la distancia minima
        
        return nuevo; // Retorna el nuevo aeropuerto agregado

}
void airTripJoin(struct airTrip** tripJoin, struct airTrip* trip1, struct airTrip* trip2){

    /*
    Consigna: Une dos recorridos borrando los recorridos pasados por parámetro y retornando un nuevo recorrido en el doble puntero. Los recorridos serán unidos directamente colocando todas las paradas del trip1 y luego todas las paradas del trip2. Si el nombre del avión en ambos recorridos es el mismo, entonces se dejará solo este nombre. Si los nombres son diferentes, se deberá construir una nueva string que concatene el nombre del primero con el nombre del segundo separados por un guión. Por ejemplo, si el avión era un "Boeing737" para un recorrido y "Boeing747" para el otro, el nombre resultante será "Boeing737-Boeing747"
    */
   struct airTrip* nuevo = (struct airTrip*) malloc(sizeof(struct airTrip)); // struct airTrip* guarda el nuevo recorrido
    nuevo->plane = strDup(trip1->plane); // Aca se copia el nombre del avion del primer recorrido en el nuevo recorrido
    nuevo->totalLength = trip1->totalLength + trip2->totalLength; // Aca se calcula la longitud total del nuevo recorrido
    nuevo->first = trip1->first; // Aca se copia el primer aeropuerto del primer recorrido en el nuevo recorrido
    struct airport* actual = trip1->first; // struct airport* guarda el aeropuerto actual
    while (actual->next != NULL){ // Mientras el aeropuerto actual no sea el ultimo de la lista
        actual = actual->next; // El aeropuerto actual pasa a ser el aeropuerto siguiente al actual
    }
    actual->next = trip2->first; // El aeropuerto siguiente al actual pasa a ser el primer aeropuerto del segundo recorrido
    if (strcmp(trip1->plane, trip2->plane) != 0){ // Si el nombre del avion del primer recorrido es distinto al nombre del avion del segundo recorrido
        nuevo->plane = strDup(trip1->plane); // Aca se copia el nombre del avion del primer recorrido en el nuevo recorrido
        nuevo->plane = strCat(nuevo->plane, "-"); // Aca se agrega un guion al nombre del avion del nuevo recorrido
        nuevo->plane = strCat(nuevo->plane, trip2->plane); // Aca se agrega el nombre del avion del segundo recorrido al nombre del avion del nuevo recorrido
    }
    free(trip1); // Se libera el primer recorrido
    free(trip2); // Se libera el segundo recorrido
    *tripJoin = nuevo; // El doble puntero tripJoin pasa a ser el nuevo recorrido
    return nuevo; // Retorna el nuevo recorrido

}

void airTripDelLast(struct airTrip* trip) {
/*
Consigna: Borra la última parada de un recorrido. Para esto debe liberar la memoria, tanto del nodo como del string del nombre
*/
    struct airport* actual = trip->first; // struct airport* guarda el aeropuerto actual
    struct airport* anterior = NULL; // struct airport* guarda el aeropuerto anterior al aeropuerto actual
    while (actual->next != NULL){ // Mientras el aeropuerto actual no sea el ultimo de la lista
        anterior = actual; // El aeropuerto anterior al actual pasa a ser el aeropuerto actual
        actual = actual->next; // El aeropuerto actual pasa a ser el aeropuerto siguiente al actual
    }
    free(actual->name); // Se libera el nombre del aeropuerto actual
    free(actual); // Se libera el aeropuerto actual
    anterior->next = NULL; // El aeropuerto siguiente al anterior pasa a ser NULL
    return; // Retorna

}

void airTripRemoveDuplicates(struct airTrip* trip) {
/*
Consigna: Borra todas las paradas duplicadas dentro de un recorrido, dejando solo la primer aparición de cada una
*/
    struct airport* actual = trip->first; // struct airport* guarda el aeropuerto actual
    struct airport* anterior = NULL; // struct airport* guarda el aeropuerto anterior al aeropuerto actual
    struct airport* siguiente = NULL; // struct airport* guarda el aeropuerto siguiente al aeropuerto actual
    while (actual != NULL){ // Mientras el aeropuerto actual no sea NULL
        siguiente = actual->next; // El aeropuerto siguiente al actual pasa a ser el aeropuerto siguiente al actual
        while (siguiente != NULL){ // Mientras el aeropuerto siguiente al actual no sea NULL
            if (strcmp(actual->name, siguiente->name) == 0){ // Si el nombre del aeropuerto actual es igual al nombre del aeropuerto siguiente al actual
                anterior->next = siguiente->next; // El aeropuerto siguiente al anterior pasa a ser el aeropuerto siguiente al siguiente
                free(siguiente->name); // Se libera el nombre del aeropuerto siguiente
                free(siguiente); // Se libera el aeropuerto siguiente
                siguiente = anterior->next; // El aeropuerto siguiente pasa a ser el aeropuerto siguiente al anterior
            } else { // Si el nombre del aeropuerto actual no es igual al nombre del aeropuerto siguiente al actual
                anterior = siguiente; // El aeropuerto anterior pasa a ser el aeropuerto siguiente
                siguiente = siguiente->next; // El aeropuerto siguiente pasa a ser el aeropuerto siguiente al siguiente
            }
        }
        anterior = actual; // El aeropuerto anterior pasa a ser el aeropuerto actual
        actual = actual->next; // El aeropuerto actual pasa a ser el aeropuerto siguiente al actual
    }
    return; // Retorna


}

char* airTripGetTrip(struct airTrip* trip) {
/* 
Consigna: Retorna una string con los nombres de todas las paradas del recorrido separadas por un guión. Si le paso un recorrido con paradas A B C D E, retorna "A-B-C-D-E"
*/
    char* string = (char*) malloc(sizeof(char)); // char* guarda la string
    string[0] = '\0'; // La string pasa a ser NULL
    struct airport* actual = trip->first; // struct airport* guarda el aeropuerto actual
    while (actual != NULL){ // Mientras el aeropuerto actual no sea NULL
        string = strCat(string, actual->name); // A la string se le agrega el nombre del aeropuerto actual
        if (actual->next != NULL){ // Si el aeropuerto siguiente al actual no es NULL
            string = strCat(string, "-"); // A la string se le agrega un guion
        }
        actual = actual->next; // El aeropuerto actual pasa a ser el aeropuerto siguiente al actual
    }
    return string; // Retorna la string
}

void airTripPrint(struct airTrip* trip) {
    printf("%s : %.2f\n", trip->plane, trip->totalLength);
    struct airport* ap = trip->first;
    while(ap != 0) {
        printf("[%s:(%.2f,%.2f)]",ap->name,ap->latitude,ap->longitude);
        ap = ap->next;
    }
    if(trip->first != 0) {
        printf("\n");
    }
}

void airTripDelete(struct airTrip* trip) {
/*
Consigna: borra todos los datos del recorrido pasado por parámetro. Debe para esto llamar a la funcion free para cada una de las estructuras y strings referenciadas
*/
    struct airport* ap = trip->first; // struct airport* guarda el aeropuerto actual
    while(ap != 0) { // Mientras el aeropuerto actual no sea NULL
        struct airport* next = ap->next; // struct airport* guarda el aeropuerto siguiente al aeropuerto actual
        free(ap->name); // Se libera el nombre del aeropuerto actual
        free(ap); // Se libera el aeropuerto actual
        ap = next; // El aeropuerto actual pasa a ser el aeropuerto siguiente al actual
    }
    free(trip->plane);
    free(trip);
}