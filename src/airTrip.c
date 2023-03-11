#include "airTrip.h"

char* strDup(char* src) {
    /*
     Esta función hace una copia del string src en una nueva área de memoria 
     y retorna el puntero a la nueva copia. Además, se asegura de reservar 
     la memoria necesaria con malloc y de copiar todos los caracteres del 
     string utilizando un bucle while. La última posición de la nueva cadena 
     es asignada como el caracter nulo \0, para indicar el fin del string.
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
    Esta función concatena dos strings y retorna un puntero a la nueva cadena.
    */
    if (src1 == NULL || src2 == NULL) {
        return NULL;
    }

    int len1 = 0;
    while (src1[len1] != '\0') {
        len1++;
    }

    int len2 = 0;
    while (src2[len2] != '\0') {
        len2++;
    }

    char* dest = (char*) malloc(sizeof(char) * (len1 + len2 + 1));
    if (dest == NULL) {
        return NULL;
    }

    int i = 0;
    while (src1[i] != '\0') {
        dest[i] = src1[i];
        i++;
    }

    int j = 0;
    while (src2[j] != '\0') {
        dest[i] = src2[j];
        i++;
        j++;
    }

    dest[i] = '\0';

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

    // COMPLETAR

}

void airTripAddBest(struct airTrip* trip, char* name, float longitude, float latitude) {

    // COMPLETAR

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


