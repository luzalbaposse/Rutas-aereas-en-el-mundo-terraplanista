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

void airTripAddBest(struct airTrip* trip, char* name, float longitude, float latitude) {

struct airport *actual = trip->first;
    struct airport* nuevo = (struct airport*) malloc(sizeof(struct airport));
    nuevo->name = strDup(name);
    nuevo->longitude = longitude;
    nuevo->latitude = latitude;
    nuevo->next = NULL;
    int lugar = 0;
    int contador = 1;

    if (trip->first == NULL) {
        trip->first = nuevo;
        trip->totalLength = 0;
        return;
    }

    float longitudTotal = trip->totalLength; // longitud total del viaje
    // ir hasta el ultimo aeropuerto en la lista
    struct airport *current = trip->first;
    while (current->next != NULL){
        current = current->next;
    }
    float longitudTotalFinal = longitudTotal + flyLength(current, nuevo); // longitud total del viaje si agregamos el nuevo aeropuerto al final de la lista de aeropuertos
    struct airport* mejorLugar = actual; // mejor lugar para agregar el nuevo aeropuerto
    while (actual->next != NULL){   // recorremos la lista de aeropuertos
        float longitudTotalActual = longitudTotal + flyLength(actual, nuevo) + flyLength(nuevo, actual->next);
        // longitud total del viaje si agregamos el nuevo aeropuerto en el lugar actual
        if (longitudTotalActual < longitudTotalFinal){ // si la longitud total del viaje es menor si agregamos el nuevo en el lugar actual, entonces agregamos el nuevo en el lugar actual
            longitudTotalFinal = longitudTotalActual;
            mejorLugar = nuevo;
            lugar++;
        }
     
        // Chequeamos todas las posiciones, entonces utilizamos el contador para elegir cual es el mejor lugar.
       
    }
       actual = actual->next; // avanzamos al siguiente aeropuerto
        if (lugar == 0){
            current->next = nuevo; 
        } else {
                while (current->next != NULL){
                    if (contador == lugar){
                    nuevo->next = current -> next;
                    current -> next = nuevo;

                    break;
                    }
                    contador++;
                    current = current -> next;

            }
        }


}

void airTripJoin(struct airTrip** tripJoin, struct airTrip* trip1, struct airTrip* trip2){

    // COMPLETAR

}

void airTripDelLast(struct airTrip* trip) {

    // COMPLETAR

}

void airTripRemoveDuplicates(struct airTrip* trip) {

    // COMPLETAR

}

char* airTripGetTrip(struct airTrip* trip) {

    // COMPLETAR

    return 0;
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
    struct airport* ap = trip->first;
    while(ap != 0) {
        struct airport* next = ap->next;
        free(ap->name);
        free(ap);
        ap = next;
    }
    free(trip->plane);
    free(trip);
}


