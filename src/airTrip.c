#include "airTrip.h"

char* strDup(char* src) {
    /*
    Para esta función, pensamos el siguiente algoritmo:
    1. Calculamos el largo del string.
    2. Reservamos memoria para la nueva cadena.
    3. Copiamos el string en la nueva cadena.
    4. Retornamos el puntero a la nueva cadena.
    En resumen, la función recibe un string y retorna un nuevo string que es una copia 
    del string que recibimos.
    */
    if (src == NULL){
        return NULL;
    }
    int len = 0;
    while (src[len] != '\0'){
        len++;
    }
    char* dest = (char*) malloc(sizeof(char) * (len + 1));
    int i = 0;
    while (src[i] != '\0'){
        dest[i] = src[i];
        i++;
    }

    return dest;
}

int strCmp(char*a, char* b) {
    /*
     Esta función compara dos strings y retorna un valor negativo si s1 es 
     menor que s2, 0 si son iguales y un valor positivo si s1 es mayor que s2.
    */
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] < b[i]) {
            return 1;
        } else if (a[i] > b[i]) {
            return -1;
        }
        i++;
    }
    if (a[i] == '\0' && b[i] == '\0') {
        return 0;
    } else if (a[i] == '\0') {
        return 1;
    } else {
        return -1;
    }
}


char* strConcatenate(char* src1, char* src2) {
    /*
    El algoritmo que pensamos para esta función es el siguiente:
    1. Calculamos el largo de cada string.
    2. Reservamos memoria para la nueva cadena.
    3. Copiamos el primer string en la nueva cadena.
    4. Copiamos el segundo string en la nueva cadena.
    5. Agregamos el caracter nulo al final de la cadena.
    6. Retornamos el puntero a la nueva cadena.
    En palabras simples, la función recibe dos strings y retorna un nuevo string que es la suma de estos dos.
    */
    if (src1 == NULL || src2 == NULL) { // Si alguno de los strings es NULL, retorna NULL
        return NULL;
    }

    int len1 = 0;
    while (src1[len1] != '\0') { // Calcula el largo de src1
        len1++;
    }

    int len2 = 0;
    while (src2[len2] != '\0') { // Calcula el largo de src2
        len2++;
    }

    char* dest = (char*) malloc(sizeof(char) * (len1 + len2 + 1)); // Reserva memoria para la nueva cadena
    if (dest == NULL) { // Si no se pudo reservar memoria, retorna NULL
        return NULL; 
    }

    int i = 0; // Copia src1 en la nueva cadena
    while (src1[i] != '\0') {
        dest[i] = src1[i];
        i++;
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

    Desarrollo:

    El algoritmo que pensamos para esta función es el siguiente:
    1. Reservamos memoria para el nuevo aeropuerto.
    2. Copiamos el nombre del aeropuerto en el nuevo aeropuerto.
    3. Copiamos la longitud y latitud del aeropuerto en el nuevo aeropuerto.
    4. Agregamos el nuevo aeropuerto al final de la lista de aeropuertos.
    5. Calculamos la longitud total del viaje.
    6. Retornamos el puntero al nuevo aeropuerto.

    Requiere: trip != NULL && name != NULL
    Devuelve: el nuevo aeropuerto agregado.
    */

    struct airport* actual = trip->first;
    while (actual->next != NULL){
        actual = actual->next;
    }
    struct airport* nuevo = (struct airport*) malloc(sizeof(struct airport));
    nuevo->name = strDup(name);
    nuevo->longitude = longitude;
    nuevo->latitude = latitude;
    nuevo->next = NULL;
    trip->totalLength += flyLength(actual, nuevo);

} 


void airTripAddBest(struct airTrip *trip, char *name, float longitude,
                    float latitude) {
  // creamos el nuevo aeropuerto con la información pasada por parámetro
  struct airport *nuevo = (struct airport *)malloc(sizeof(struct airport));
  nuevo->name = strDup(name);
  nuevo->longitude = longitude;
  nuevo->latitude = latitude;
  nuevo->next = NULL;
  // Ahora, si la lista está vacía, lo que vamos a hacer es agregar el nuevo
  // aeropuerto como el primero
  if (trip->first == NULL) {
    trip->first = nuevo;
    return;
  }
  // Si la lista no está vacía, pero tiene solamente un elemento, lo que vamos a
  // hacer es agregar el nuevo aeropuerto como el segundo
  if (trip->first->next == NULL) {
    trip->first->next = nuevo;
    trip->totalLength = flyLength(trip->first, nuevo);
    return;
  }
  // Si la lista ya tiene más de un elemento, vamos a calcular la longitud del
  // vuelo si se agrega el nuevo aeropuerto entre el primer aeropuerto y el
  // segundo aeropuerto
  float length1 = flyLength(trip->first, nuevo) + flyLength(nuevo, trip->first->next);
  // Ahora vamos a recorrer la lista de aeropuertos calculando la longitud del
  // vuelo si se agrega entre cada par de aeropuertos consecutivos, sin eliminar
  // ningun aeropuerto que ya esté en la lista
  struct airport *actual = trip->first;
  float length2 = 0.0;
  struct airport *correcto = trip->first;
  while (actual->next != NULL) {
    length2 = flyLength(actual, nuevo) + flyLength(nuevo, actual->next);
    if (length2 < length1) {
      correcto = actual;
    }
    actual = actual->next;
  }
  // Si la longitud del vuelo es menor, entonces agregamos el nuevo aeropuerto
  // entre el aeropuerto actual y el siguiente
  nuevo->next = correcto->next;
  correcto->next = nuevo;
  trip->totalLength = trip->totalLength + flyLength(correcto, nuevo);
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
Borra todas las paradas duplicadas dentro de un recorrido, dejando solo la primer aparición de cada una.
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
                siguiente = anterior->next; // El aeropuerto siguiente al actual pasa a ser el aeropuerto siguiente al anterior
            }
            else{ // Si el nombre del aeropuerto actual no es igual al nombre del aeropuerto siguiente al actual
                anterior = siguiente; // El aeropuerto anterior al actual pasa a ser el aeropuerto siguiente al actual
                siguiente = siguiente->next; // El aeropuerto siguiente al actual pasa a ser el aeropuerto siguiente al siguiente
            }
        }
        actual = actual->next; // El aeropuerto actual pasa a ser el aeropuerto siguiente al actual
        anterior = NULL; // El aeropuerto anterior al actual pasa a ser NULL
    }
    return;
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