#include "airTrip.h"

char *strDup(char *src) {
  if (src == NULL) { // Si el string es NULL, retornamos NULL
    return NULL;
  }
  int len = 0;
  // Mientras no lleguemos al final del string
  while (src[len] != '\0') {
    // Incrementamos el contador
    len++;
  }
  // Reservamos memoria para el nuevo string
  char *dest = (char *)malloc(sizeof(char) * (len + 1));
  int i = 0;
  // Mientras no lleguemos al final del string copiamos el caracter
  while (src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
  // Retornamos el puntero al nuevo string
  return dest;
}

int strCmp(char *a, char *b) {
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

char *strCnt(char *src1, char *src2) {
  if (src1 == NULL ||
      src2 == NULL) { 
    // Si alguno de los strings es NULL, retorna NULL
    return NULL;
    // Retorna NULL
  }
  int len1 = 0;
  while (src1[len1] != '\0') { 
    // Calculamos el largo de src1
    len1++;                    
  }
  int len2 = 0;
  while (src2[len2] != '\0') { // Calculamos el largo de src2
    len2++;                    
  }

  char *dest = (char *)malloc(
      sizeof(char) * (len1 + len2 + 1)); // Reservamos memoria para la nueva cadena
  if (dest == NULL) { // Si no se pudo reservar memoria, retorna NULL
    return NULL;
  }

  int i = 0;                // Copiamos src1 en la nueva cadena
  while (src1[i] != '\0') { // Mientras no lleguemos al final de src1
    dest[i] = src1[i];      // Copiamos el caracter
    i++;                    
  }

  int j = 0;
  while (src2[j] != '\0') { // Copiamos src2 en la nueva cadena
    dest[i] = src2[j];
    i++;
    j++;
  }

  dest[i] = '\0'; // Agregamos el caracter nulo al final de la cadena

  return dest;
}

float flyLength(struct airport *a1, struct airport *a2) {
  float deltaLon = a1->longitude - a2->longitude;
  float deltaLat = a1->latitude - a2->latitude;
  return sqrt(deltaLon * deltaLon + deltaLat * deltaLat);
}

struct airTrip *airTripNew(char *plane) {
  struct airTrip *at = (struct airTrip *)malloc(sizeof(struct airTrip));
  at->plane = strDup(plane);
  at->first = 0;
  at->totalLength = 0.0;
  return at;
}

void airTripAddLast(struct airTrip *trip, char *name, float longitude, float latitude) {
  // Creamos el nuevo aeropuerto con los datos pasados por parámetro
  struct airport *nuevo = (struct airport *)malloc(sizeof(struct airport));
  nuevo->name = strDup(name);
  nuevo->longitude = longitude;
  nuevo->latitude = latitude;
  nuevo->next = NULL;
  // Si la lista está vacía, el nuevo aeropuerto es el primero
  if (trip->first == NULL) {
    trip->first = nuevo;
  } else {
  // Si la lista no está vacía, vamos a recorrerla hasta llegar al último
    struct airport *actual = trip->first;
    while (actual->next != NULL) {
      actual = actual->next;
    }
    // Agregamos el nuevo aeropuerto al final de la lista
    actual->next = nuevo;
    // Actualizamos la longitud total del viaje
    trip->totalLength += flyLength(actual, nuevo);
  }
}

void airTripAddBest(struct airTrip *trip, char *name, float longitude,float latitude) {
  // Creamos el nuevo aeropuerto con la información pasada por parámetro
  struct airport *nuevo = (struct airport *)malloc(sizeof(struct airport));
  nuevo->name = strDup(name);
  nuevo->longitude = longitude;
  nuevo->latitude = latitude;
  nuevo->next = NULL;
  // Ahora, si la lista está vacía, lo que vamos a hacer es agregar el nuevo aeropuerto como el primero
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
  while (actual->next != NULL) {
  // Si la longitud del vuelo es menor, entonces agregamos el nuevo aeropuerto
    length2 = flyLength(actual, nuevo) + flyLength(nuevo, actual->next);
    if (length2 < length1) {
      correcto = actual;
    }
    // Entre el aeropuerto actual y el siguiente aeropuerto de la lista
    if (strCmp(nuevo->name, actual->name) == 0){
      correcto = actual;
      break;
    }
    actual = actual->next;
  }
  // Si la longitud del vuelo es menor, entonces agregamos el nuevo aeropuerto
  if (trip->totalLength + flyLength(actual, nuevo) < trip->totalLength + length2 - flyLength(correcto, correcto->next)){
    correcto = actual;
  }
  if (trip->totalLength + flyLength(trip->first, nuevo) + flyLength(nuevo, trip->first->next) - flyLength(trip->first, trip->first->next) < trip->totalLength + flyLength(actual, nuevo)){
    correcto = trip->first;
  } 
  if (correcto->next == NULL){ // Si el aeropuerto correcto es el ultimo de la lista
    correcto->next = nuevo; // Agregamos el nuevo aeropuerto al final de la lista
    trip->totalLength += flyLength(correcto, nuevo);
  }else{ // Si el aeropuerto correcto no es el ultimo de la lista
    nuevo->next = correcto->next; // Agregamos el nuevo aeropuerto entre el aeropuerto correcto y el siguiente
    correcto->next = nuevo;
    trip->totalLength = trip->totalLength + flyLength(correcto, nuevo) + flyLength(nuevo, nuevo->next) - flyLength(correcto, nuevo->next);
  }
}


void airTripJoin(struct airTrip **tripJoin, struct airTrip *trip1, struct airTrip *trip2) {
  // Creamos un struct airTrip nuevo con los datos del primer recorrido y del segundo recorrido
  struct airTrip *nuevo = (struct airTrip *)malloc(sizeof(struct airTrip)); 
  nuevo->plane = strDup(trip1->plane); 
  nuevo->totalLength = trip1->totalLength + trip2->totalLength;
  nuevo->first = trip1->first; 
  // Creamos un airport auxiliar para recorrer la lista de aeropuertos del primer recorrido
  struct airport *actual = trip1->first; 
  // Mientras el aeropuerto siguiente no sea NULL, seguimos recorriendo la lista
  while (actual->next != NULL) { 
    actual = actual->next; 
  }
  // Agregamos la longitud del vuelo entre el ultimo aeropuerto del primer recorrido y el primer aeropuerto del segundo recorrido
  nuevo->totalLength += flyLength(actual, trip2->first);
  actual->next = trip2->first;
  if (strCmp(trip1->plane, trip2->plane) !=0) { 
  // Si los aviones son distintos, se agrega un guion al nombre del avion
    nuevo->plane = strCnt(nuevo->plane,"-"); 
    nuevo->plane = strCnt(nuevo->plane,trip2->plane);
  free(trip1);       
  free(trip2);       
  *tripJoin = nuevo;
}
}

void airTripDelLast(struct airTrip *trip) {
  // Creamos airport actual y airport anterior para recorrer la lista de aeropuertos, funcionan como auxiliares
  struct airport *actual = trip->first; 
  struct airport *anterior = NULL;
  while (actual->next != NULL) {
    // Si se cumple que el aeropuerto siguiente al actual es NULL, entonces el aeropuerto actual es el ultimo de la lista
    anterior = actual;     
    actual = actual->next; 

  }
  trip->totalLength = trip->totalLength - flyLength(anterior, actual);
  free(actual->name);    // Se libera el nombre del aeropuerto actual
  free(actual);          // Se libera el aeropuerto actual
  anterior->next = NULL; // El aeropuerto siguiente al anterior pasa a ser NULL

}

void airTripRemoveDuplicates(struct airTrip* trip) {  
  // Creamos 3 structs airport auxiliar para recorrer la lista de aeropuertos
  struct airport* actual = trip->first; 
  struct airport* eliminar; 
  struct airport* siguiente; 
  trip->totalLength = 0;
  while (actual->next != NULL){ // Mientras el aeropuerto actual no sea NULL
    siguiente = actual->next; // el aeropuerto siguiente al actual pasa a ser el aeropuerto siguiente al actual
    while(siguiente != NULL){  
      if (strCmp(actual->name, siguiente->name) == 0){ // Si el nombre del aeropuerto actual es igual al nombre del aeropuerto siguiente al actual
        eliminar = siguiente; // El aeropuerto siguiente al anterior pasa a ser el aeropuerto siguiente al siguiente
        if (siguiente->next == NULL){
          actual->next = NULL;
        }else{
          actual->next = siguiente->next; // El aeropuerto siguiente pasa a ser el aeropuerto siguiente al anterior
        }
        free(eliminar);
      }  
      siguiente = siguiente->next;
    }  
    trip->totalLength += flyLength(actual, actual->next);// Se van sumando los aeropuertos de uno en uno, luego de eliminar los duplicados
    actual = actual->next; // El aeropuerto actual pasa a ser el aeropuerto siguiente al actual
  }
}


char *airTripGetTrip(struct airTrip *trip) {
  // Creamos un string auxiliar para concatenar los nombres de los aeropuertos
  char* viaje = (char*)malloc(sizeof(char)); 
  // Si el vuelo es NULL, retornamos el string vacio
  if (trip == NULL){
    return viaje;
  }
  // Creamos un struct airport auxiliar para recorrer la lista de aeropuertos
  struct airport* actual = trip->first;
  viaje = strCnt(viaje, actual->name);
  // Mientras el aeropuerto siguiente no sea NULL, seguimos recorriendo la lista y lo que vamos a hacer es concatenar los nombres de los aeropuertos
  while (actual->next != NULL){ 
    viaje = strCnt(viaje,"-");
    viaje = strCnt(viaje, actual->next->name);
    actual = actual->next;
  }
  return viaje;
}

void airTripPrint(struct airTrip *trip) {
  printf("%s : %.2f\n", trip->plane, trip->totalLength);
  struct airport *ap = trip->first;
  while (ap != 0) {
    printf("[%s:(%.2f,%.2f)]", ap->name, ap->latitude, ap->longitude);
    ap = ap->next;
  }
  if (trip->first != 0) {
    printf("\n");
  }
}

void airTripDelete(struct airTrip *trip) {
  struct airport *ap = trip->first;
  while (ap != 0) {
    struct airport *next = ap->next;
    free(ap->name);
    free(ap);
    ap = next;
  }
  free(trip->plane);
  free(trip);
}
