#include "airTrip.h"

char* strDup(char* src) {
    /*
    Esta función recibe un string y retorna un nuevo string que es una copia del string recibido.
    */
    if (src == NULL){ // Si está vacío, no retornamos nada
        return NULL;
    }
    int len = 0;
    while (src[len] != '\0'){ // Vamos a calcular el largo del string para después reservar memoria
        len++;
    }
    char* dest = (char*) malloc(sizeof(char) * (len + 1)); // Reservamos memoria para el nuevo string
    int i = 0;
    while (src[i] != '\0'){ // Acá vamos a copiar el string a medida que recorremos la cadena
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
    while (a[i] != '\0' && b[i] != '\0') { // Recorre los strings hasta que uno de los dos llegue al final
        if (a[i] < b[i]) { // Si el caracter del primero es menor que el segundo, retorna 1
            return 1;
        } else if (a[i] > b[i]) { // Si el caracter del primero es mayor que el segundo, retorna -1
            return -1;
        }
        i++;
    }
    if (a[i] == '\0' && b[i] == '\0') { // Si ambos strings llegaron al final, retorna 0
        return 0;
    } else if (a[i] == '\0') { // Si el primer string llegó al final, retorna 1
        return 1;
    } else { // Si el segundo string llegó al final, retorna -1 
        return -1;
    }
}


char* strConcatenate(char* src1, char* src2) {
    /*
    Esta función recibe dos strings y retorna un nuevo string que es la concatenación de los dos strings recibidos.
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
    Esta función recibe un struct airTrip, un string con el nombre del aeropuerto, la longitud y la latitud del aeropuerto. Devuelve un struct airTrip con el nuevo aeropuerto agregado al final de la lista.
    */
    
    struct airport* actual = trip->first; // Con este nos vamos a mover por la lista
    struct airport* nuevo = (struct airport*) malloc(sizeof(struct airport)); // Creamos el nuevo aeropuerto con la información pasada por parámetro
    nuevo->name = strDup(name);
    nuevo->longitude = longitude;
    nuevo->latitude = latitude;
    nuevo->next = NULL;
    while (actual->next != NULL){ // Recorremos la lista hasta llegar al último aeropuerto
        actual = actual->next; // Vamos avanzando al siguiente aeropuerto
    } 
    trip->totalLength += flyLength(actual, nuevo); // Actualizamos la longitud total del vuelo

} 


void airTripAddBest(struct airTrip *trip, char *name, float longitude, float latitude) {
    /*
    Esta función recibe un struct airTrip, un string con el nombre del aeropuerto, la longitud y la latitud del aeropuerto. Devuelve un struct airTrip con el nuevo aeropuerto agregado en la posición que minimiza la longitud total del vuelo.
    */
    // creamos el nuevo aeropuerto con la información pasada por parámetro
    struct airport *nuevo = (struct airport *)malloc(sizeof(struct airport));
    nuevo->name = strDup(name);
    nuevo->longitude = longitude;
    nuevo->latitude = latitude;
    nuevo->next = NULL;
    //Ahora, si la lista está vacía, lo que vamos a hacer es agregar el nuevo aeropuerto como el primero
  if (trip->first == NULL) {
    trip->first = nuevo;
    return;
  }

  // Si la lista no está vacía, pero tiene solamente un elemento, lo que vamos a hacer es agregar el nuevo aeropuerto como el segundo
  
  if (trip->first->next == NULL) {
    trip->first->next = nuevo;
    trip->totalLength = flyLength(trip->first, nuevo);
    return;
  }
   
  // Si la lista ya tiene más de un elemento, vamos a calcular la longitud del vuelo si se agrega el nuevo aeropuerto entre el primer aeropuerto y el segundo aeropuerto
  
  float length1 = flyLength(trip->first, nuevo) + flyLength(nuevo, trip->first->next);
  
  // Ahora vamos a recorrer la lista de aeropuertos calculando la longitud del vuelo si se agrega entre cada par de aeropuertos consecutivos, sin eliminar ningun aeropuerto que ya esté en la lista
  struct airport *actual = trip->first;
  float length2 = 0.0;
  struct airport *correcto = trip->first;
  correcto = actual;
  while (actual->next != NULL) { // Recorremos la lista hasta llegar al último aeropuerto

    length2 = flyLength(actual, nuevo) + flyLength(nuevo, actual->next); // Calculamos la longitud del vuelo si se agrega el nuevo aeropuerto entre el aeropuerto actual y el siguiente

    if (length2 < length1) { // Si la longitud del vuelo es menor, entonces agregamos el nuevo aeropuerto entre el aeropuerto actual y el siguiente
      correcto = actual;
    }
    if (strCmp(nuevo->name, actual->name) == 0){ // Si el nombre del aeropuerto es igual al nombre del aeropuerto actual, entonces agregamos el nuevo aeropuerto entre el aeropuerto actual y el siguiente
      correcto = actual;
      break;
    }
    actual = actual->next; // Vamos avanzando al siguiente aeropuerto
  }
  
  if (trip->totalLength + flyLength(actual, nuevo) < trip->totalLength + length2 - flyLength(correcto, correcto->next)){ // Si la longitud del vuelo es menor, entonces agregamos el nuevo aeropuerto entre el aeropuerto actual y el siguiente
    correcto = actual;
  }
  if (trip->totalLength + flyLength(trip->first, nuevo) + flyLength(nuevo, trip->first->next) - flyLength(trip->first, trip->first->next) < trip->totalLength + flyLength(actual, nuevo)){ // Si la longitud del vuelo es menor, entonces agregamos el nuevo aeropuerto entre el aeropuerto actual y el siguiente
    correcto = trip->first;
  }
  
  // Si la longitud del vuelo es menor, entonces agregamos el nuevo aeropuerto entre el aeropuerto actual y el siguiente
  if (correcto->next == NULL){
    correcto->next = nuevo;
    trip->totalLength += flyLength(correcto, nuevo);
  }else{ // Si la longitud del vuelo es mayor, entonces agregamos el nuevo aeropuerto entre el aeropuerto actual y el siguiente
    nuevo->next = correcto->next;
    correcto->next = nuevo;
    trip->totalLength = trip->totalLength + flyLength(correcto, nuevo) + flyLength(nuevo, nuevo->next) - flyLength(correcto, nuevo->next);
  }
}

void airTripJoin(struct airTrip** tripJoin, struct airTrip* trip1, struct airTrip* trip2){
    /*
        Esta función recibe dos struct airTrip y devuelve un struct airTrip con los dos recorridos unidos.
    */
    // Creamos el nuevo struct airTrip
    struct airTrip* nuevo = (struct airTrip*) malloc(sizeof(struct airTrip)); 
    nuevo->plane = strDup(trip1->plane); 
    nuevo->totalLength = trip1->totalLength + trip2->totalLength; 
    nuevo->first = trip1->first; 
    // Recorremos la lista de aeropuertos del primer recorrido hasta llegar al último
    struct airport* actual = trip1->first;
    while (actual->next != NULL){ 
        actual = actual->next; 
    }
    // Agregamos el primer aeropuerto del segundo recorrido al final del primer recorrido
    actual->next = trip2->first; 
    if (strcmp(trip1->plane, trip2->plane) != 0){ 
        nuevo->plane = strDup(trip1->plane); 
        nuevo->plane = strCat(nuevo->plane, "-"); 
        nuevo->plane = strCat(nuevo->plane, trip2->plane); 
    }
    // Liberamos la memoria de los dos recorridos que se unieron
    free(trip1);
    free(trip2); 
    *tripJoin = nuevo; 
    return nuevo; 

}

void airTripDelLast(struct airTrip* trip) {
/*
Esta función recibe un struct airTrip y elimina el último aeropuerto de la lista de aeropuertos del recorrido.
*/
    struct airport* actual = trip->first; 
    // Recorremos la lista de aeropuertos hasta llegar al último
    struct airport* anterior = NULL; 
    while (actual->next != NULL){ // Mientras el aeropuerto siguiente al actual no sea NULL
        anterior = actual;          // El aeropuerto anterior al actual pasa a ser el aeropuerto actual
        actual = actual->next;      // El aeropuerto actual pasa a ser el aeropuerto siguiente al actual
    }
    // Liberamos la memoria del último aeropuerto
    free(actual->name); 
    free(actual); 
    anterior->next = NULL; 
    return; 

}
void airTripRemoveDuplicates(struct airTrip* trip) {
    /*
    Esta función borra todas las paradas duplicadas dentro de un recorrido, dejando solo la primer aparición de cada una.
    */
   
  struct airport* actual = trip->first; // struct airport* guarda el aeropuerto actual
  struct airport* eliminar; // struct airport* guarda el aeropuerto anterior al aeropuerto actual
  struct airport* siguiente; // struct airport* guarda el aeropuerto siguiente al aeropuerto actual
  while (actual != NULL){ // Mientras el aeropuerto actual no sea NULL
    siguiente = actual->next; // El aeropuerto siguiente al actual pasa a ser el aeropuerto siguiente al actual
    while(siguiente != NULL){  
      if (strCmp(actual->name, siguiente->name) == 0){ // Si el nombre del aeropuerto actual es igual al nombre del aeropuerto siguiente al actual
        eliminar = siguiente; // El aeropuerto siguiente al anterior pasa a ser el aeropuerto siguiente al siguiente
        if (siguiente->next == NULL){
          trip->totalLength -= flyLength(actual, eliminar);
          actual->next = NULL;
        }else{
          trip->totalLength = trip->totalLength - flyLength(actual, eliminar) - flyLength(eliminar, siguiente->next) + flyLength(actual, siguiente->next);
          actual->next = siguiente->next; // El aeropuerto siguiente pasa a ser el aeropuerto siguiente al anterior
        }
        free(eliminar);
      }  

      siguiente = siguiente->next;
    }  
    actual = actual->next; // El aeropuerto actual pasa a ser el aeropuerto siguiente al actual
  }
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
