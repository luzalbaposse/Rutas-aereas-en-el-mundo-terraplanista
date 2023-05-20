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
  // Agregamos el terminador nulo al final del string
  dest[i] = '\0';
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
  
  if (src1 == NULL || src2 == NULL) { // Si src1 es NULL o src2 es NULL, retornamos una copia del string no NULL
    return strDup(src1 != NULL ? src1 : src2); 
  }

  if (src1 == NULL && src2 == NULL) { // Si ambos strings son NULL, retornamos NULL
    return NULL;
  }

  int int1 = 0;
  while (src1[int1] != '\0') { // Contamos la cantidad de caracteres de src1
    int1++;
  }

  int int2 = 0;
  while (src2[int2] != '\0') { // Contamos la cantidad de caracteres de src2
    int2++;
  }

  int length = int1 + int2;
  char *strnew = (char *)malloc(sizeof(char) * (length + 1)); // Reservamos memoria para la nueva cadena

  int uno = 0;
  while (uno != int1) { // Copiamos src1 en la nueva cadena
    strnew[uno] = src1[uno];
    uno++;
  }

  int dos = 0;
  while (dos != int2) { // Copiamos src2 en la nueva cadena
    strnew[uno] = src2[dos]; 
    dos++;
    uno++;
  }

  strnew[length] = '\0';

  free(src1);
  free(src2);

  return strnew;
}

  char *dest = (char *)malloc(
      sizeof(char) * (len1 + len2 + 1)); // Reservamos memoria para la nueva cadena
  if (dest == NULL) { // Si no se pudo reservar memoria, retorna NULL
    return NULL;
  }

  int i = 0; // Copiamos src1 en la nueva cadena
  if (src1 != NULL) {
    while (src1[i] != '\0') { // Mientras no lleguemos al final de src1
      dest[i] = src1[i];      // Copiamos el caracter
      i++;                    
    }
  }

  int j = 0;
  if (src2 != NULL) {
    while (src2[j] != '\0') { // Copiamos src2 en la nueva cadena
      dest[i] = src2[j];
      i++;
      j++;
    }
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

void airTripAddBest(struct airTrip *trip, char *name, float longitude, float latitude) {
  // Crear el nuevo aeropuerto con la información pasada por parámetro
  struct airport *nuevo = (struct airport *)malloc(sizeof(struct airport));
  nuevo->name = strDup(name);
  nuevo->longitude = longitude;
  nuevo->latitude = latitude;
  nuevo->next = NULL;

  // Caso especial: Lista vacía
  if (trip->first == NULL) {
    trip->first = nuevo;
    return;
  }

  // Calcular la longitud original del primer vuelo en la lista
  float originalLength = flyLength(trip->first, trip->first->next);

  // Calcular la longitud del vuelo si se agrega el nuevo aeropuerto entre el primer aeropuerto y el siguiente aeropuerto
  float length1 = flyLength(trip->first, nuevo) + flyLength(nuevo, trip->first->next) - originalLength;

  // Recorrer la lista de aeropuertos para encontrar la mejor ubicación para el nuevo aeropuerto
  struct airport *actual = trip->first;
  struct airport *correcto = trip->first;

  while (actual->next != NULL) {
    // Calcular la longitud original del vuelo actual
    float originalLengthActual = flyLength(actual, actual->next);

    // Calcular la longitud del vuelo si se agrega el nuevo aeropuerto entre el aeropuerto actual y el siguiente aeropuerto
    float length2 = flyLength(actual, nuevo) + flyLength(nuevo, actual->next) - originalLengthActual;

    if (length2 < length1) {
      correcto = actual;
      length1 = length2;
    }

    actual = actual->next;
  }

  // Insertar el nuevo aeropuerto en la posición correcta
  nuevo->next = correcto->next; // Agregamos el nuevo aeropuerto entre el aeropuerto correcto y el siguiente
  correcto->next = nuevo;
  trip->totalLength += flyLength(correcto, nuevo) + flyLength(nuevo, nuevo->next) - originalLength; // Actualizamos la longitud total del viaje, sumando la longitud del nuevo vuelo y restando la longitud del vuelo original
}


void airTripJoin(struct airTrip** tripJoin, struct airTrip* trip1, struct airTrip* trip2) {
  char* avion; // Nombre del avión que se usará en el viaje resultante
  
  if (strCmp(trip1->plane, trip2->plane) == 0) { // trip1 y trip2 son el mismo viaje
    char* planeCopy = strDup(trip1->plane); // Copiamos el nombre del avión
    *tripJoin = airTripNew(planeCopy); // Creamos el viaje resultante
    free(planeCopy); // Liberamos la memoria
  } else { // Caso que sean viajes distintos
    avion = strCat(trip1->plane, "-"); // Concatenamos el nombre de los aviones
    avion = strCat(avion, trip2->plane); 
    *tripJoin = airTripNew(avion); // Creamos el viaje resultante
    free(avion);
  }

  //si el primero está vacío
  if (trip1->first == NULL) {
    (*tripJoin)->first = trip2->first;
    return;
  }

  // llego hasta el final de trip1
  (*tripJoin)->first = trip1->first;
  struct airport* actual = (*tripJoin)->first;
  while (actual->next != NULL) {
    actual = actual->next;
  }

  // Conecto los trips
  actual->next = trip2->first;
  (*tripJoin)->totalLength = trip1->totalLength + trip2->totalLength + flyLength(actual, trip2->first);

  // libero memoria
  free(trip1->plane);
  free(trip2->plane);
  airTripDelete(trip1);
  airTripDelete(trip2);
}


void airTripDelLast(struct airTrip *trip) {
  // Esta funcion elimina el ultimo aeropuerto de la lista
  if (trip->first == NULL) { // Si la lista está vacía, no hay nada que eliminar
    return;
  }

  struct airport *actual = trip->first; // Creamos un struct airport auxiliar para recorrer la lista de aeropuertos
  struct airport *anterior = NULL;

  while (actual->next != NULL) { // Mientras el aeropuerto actual no sea NULL
    anterior = actual;
    actual = actual->next;
  }

  if (anterior != NULL) { // Si el aeropuerto anterior no es NULL, significa que la lista tiene más de un aeropuerto
    anterior->next = NULL;
  } else {
    trip->first = NULL;
  }

  free(actual->name); // Liberamos la memoria del aeropuerto actual
  if (anterior != NULL) { // Si el aeropuerto anterior no es NULL, significa que la lista tiene más de un aeropuerto
    trip->totalLength = trip->totalLength - flyLength(anterior, actual);
  } else {
    trip->totalLength = 0.0; // Si el aeropuerto anterior es NULL, significa que la lista tiene un solo aeropuerto
  }

  free(actual); // Liberamos la memoria del aeropuerto actual
}



void airTripRemoveDuplicates(struct airTrip* trip) {
  // Esta función elimina los aeropuertos duplicados de la lista de aeropuertos del viaje
  struct airport* actual = trip->first; // Creamos un struct airport auxiliar para recorrer la lista de aeropuertos
  struct airport* eliminar;
  struct airport* siguiente;
  trip->totalLength = 0;

  while (actual != NULL) { // Mientras el aeropuerto actual no sea NULL
    siguiente = actual;

    while (siguiente->next != NULL) { // Mientras el aeropuerto siguiente no sea NULL
      if (strCmp(actual->name, siguiente->next->name) == 0) { // Si el nombre del aeropuerto actual es igual al nombre del aeropuerto siguiente
        eliminar = siguiente->next;
        siguiente->next = eliminar->next; // Eliminamos el aeropuerto siguiente

        free(eliminar->name); // Liberamos la memoria del aeropuerto eliminado
        free(eliminar); // Liberamos la memoria del aeropuerto eliminado
      } else {
        siguiente = siguiente->next; // Avanzamos al siguiente aeropuerto
      }
    }
 
    if (actual->next != NULL) { // Si el aeropuerto actual no es NULL
      trip->totalLength += flyLength(actual, actual->next); // Actualizamos la longitud total del viaje
    }

    actual = actual->next;
  }
}

char* airTripGetTrip(struct airTrip* trip) {
  // Si el vuelo es NULL, retornamos el string vacío
  if (trip->first == NULL) {
    return NULL;
  }

  // Si el vuelo tiene una única parada, retornamos una copia del nombre de esa parada
  if (trip->first->next == NULL) {
    return strDup(trip->first->name);
  }

  // Calculamos la longitud total del string resultante sumando la longitud de todos los nombres y los guiones
  int trip_len = 0;
  struct airport* current = trip->first;
  while (current != NULL) {
    trip_len += strlen(current->name);
    trip_len++; // Añadimos un espacio para el guion
    current = current->next;
  }

  // Creamos un string auxiliar con la longitud calculada
  char* viaje = (char*)malloc(sizeof(char) * (trip_len + 1));
  viaje[0] = '\0'; // Inicializamos el string vacío

  // Concatenamos los nombres de los aeropuertos separados por guiones
  current = trip->first;
  char* delimiter = ""; // String vacío como delimitador inicial
  while (current != NULL) {
    viaje = strCnt(viaje, delimiter);
    viaje = strCnt(viaje, current->name);
    delimiter = "-"; // Establecemos el guion como delimitador para las siguientes concatenaciones
    current = current->next;
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