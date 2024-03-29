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


  return strnew;
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

  struct airport* newAirport = (struct airport*) malloc(sizeof(struct airport));
  newAirport->name = strDup(name);
  newAirport->latitude = latitude;
  newAirport->longitude = longitude;
  // Se crea una nueva estructura de tipo airport y se inicializan sus propiedades con los valores de entrada
  if (trip->first == NULL) {
      // Se verifica si la primer parada del viaje es nula
      newAirport->next = NULL;
      // Si lo es, se declara a la siguiente parada como nula
      trip->first = newAirport;
      // Se agrega el nuevo airport en la primera parada
      trip->totalLength = 0;
      // Se asigna el total de longitud del viaje como 0
  } else if (trip->first->next == NULL) {
      // Se verifica si la segunda parada es nula
      newAirport->next = NULL;
      // Se declara a la parada que le sigue al nuevo airport como nula
      trip->first->next = newAirport;
      // Se asigna el nuevo airport a la segunda parada
      trip->totalLength = flyLength(trip->first, newAirport);
      // Se asigna el total de longitud del viaje a la distancia entre la primer y segunda parada
  } else {
      struct airport* current = trip->first;
      struct airport* bestPrev = trip->first;
      float minExtraLength = FLT_MAX;
      while (current->next != NULL) {
          // Se crea un ciclo que corre mientras la parada siguiente no sea nula
          float currentExtraLength = flyLength(current, newAirport) + flyLength(newAirport, current->next) - flyLength(current, current->next);
          if (currentExtraLength < minExtraLength) {
              minExtraLength = currentExtraLength;
              bestPrev = current;
          }
          current = current->next;
      }
      if (current->next == NULL) {
          // Mientras no haya una parada siguiente a la actual
          float currentExtraLength = flyLength(current, newAirport);
          if (currentExtraLength < minExtraLength) {
              minExtraLength = currentExtraLength;
              bestPrev = current;
          }
          // Se verifica si el ultimo aeropuerto de la lista es el mejor lugar para insertar el nuevo aeroperto
      }
      newAirport->next = bestPrev->next;
      bestPrev->next = newAirport;
      trip->totalLength += minExtraLength;
      // Se actualiza la longitud total del viaje sumando la longitud extra mínima
  }
}



void airTripJoin(struct airTrip** tripJoin, struct airTrip* trip1, struct airTrip* trip2) {
  
  char* TripName;
    // Variable que contendrá el nombre del avión unido

    if (strCmp(trip1->plane, trip2->plane) == 0) {
        // Se verifica si el nombre del avión en ambos recorridos es igual
        TripName = strDup(trip1->plane);
        // Se devuelve el nombre del primer avión
    } else {
        // Si los aviones tienen nombres distintos
        TripName = strCnt(trip1->plane, "-");
        char* temp = TripName;
        TripName = strCnt(TripName, trip2->plane);
        // Se unen los dos nombres de avión con un guión de por medio
        free(temp);
    }

    struct airTrip* Trip = airTripNew(TripName);
    // Se crea un nuevo airTrip con el nombre de avión unido
    free(TripName);

    struct airport* current = trip1->first;
    while (current != NULL) {
        // Agrega cada aeropuerto del primer airTrip al nuevo airTrip
        airTripAddLast(Trip, current->name, current->longitude, current->latitude);
        current = current->next;
    }

    current = trip2->first;
    while (current != NULL) {
        // Agrega cada aeropuerto del segundo airTrip al nuevo airTrip
        airTripAddLast(Trip, current->name, current->longitude, current->latitude);
        current = current->next;
    }

    *tripJoin = Trip;
    airTripDelete(trip1);
    airTripDelete(trip2);
    // Se eliminan los dos airTrip originales y se asigna el nuevo airTrip al puntero doble tripJoin

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
    return strDup("");
  }

  // Creamos un string auxiliar 
  char* viaje = strDup(trip->first->name);
  struct airport* current = trip->first->next;

  // Concatenamos los nombres de los aeropuertos separados por guiones
  while (current != NULL) {
    // Mientras la parada actual no sea nula
        char* temp = viaje;
        viaje = strCnt(viaje, "-"); // Agrega un guion al final del string de retorno
        free(temp);
        temp = viaje;
        viaje = strCnt(viaje, current->name);// Se agrega el nombre de la siguiente parada al string de retorno
        free(temp);
        current = current->next;// Cambia la parada actual a la siguiente
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