#include "airTrip.h"

char *strDup(char *src) {

  /*
  Consigna: duplica un string. Debe contar la cantidad de caracteres totales de
  src y solicitar la memoria equivalente. Luego, debe compiar todos los
  caracteres a esta nueva área de memoria. Además como valor de retorno se debe
  retornar el puntero al nuevo string
  */

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

  // Mientras no lleguemos al final del string

  while (src[i] != '\0') {
    // Copiamos el caracter
    dest[i] = src[i];
    i++;
  }

  // Retornamos el puntero al nuevo string

  return dest;
}

int strCmp(char *a, char *b) {

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

char *strCnt(char *src1, char *src2) {

  /*
     Consigna: La función toma dos strings src1 y src2, y retorna una nueva
     string que contiene una copia de todos los caracteres de src1 seguidos de
     los caracteres de src3. Esta función NO libera la memoria de las strings
     src1 y src2
     */
  if (src1 == NULL ||
      src2 == NULL) { // Si alguno de los strings es NULL, retorna NULL
    return NULL;      // Retorna NULL
  }

  int len1 = 0;
  while (src1[len1] != '\0') { // Calcula el largo de src1
    len1++;                    // Incrementa el contador
  }

  int len2 = 0;
  while (src2[len2] != '\0') { // Calcula el largo de src2
    len2++;                    // Incrementa el contador
  }

  char *dest = (char *)malloc(
      sizeof(char) * (len1 + len2 + 1)); // Reserva memoria para la nueva cadena
  if (dest == NULL) { // Si no se pudo reservar memoria, retorna NULL
    return NULL;      // Retorna NULL
  }

  int i = 0;                // Copia src1 en la nueva cadena
  while (src1[i] != '\0') { // Mientras no lleguemos al final de src1
    dest[i] = src1[i];      // Copiamos el caracter
    i++;                    // Incrementamos el contador
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

  struct airport *nuevo = (struct airport *)malloc(sizeof(struct airport));
  nuevo->name = strDup(name);
  nuevo->longitude = longitude;
  nuevo->latitude = latitude;
  nuevo->next = NULL;
  if (trip->first == NULL) {
    trip->first = nuevo;
  } else {
    struct airport *actual = trip->first;
    while (actual->next != NULL) {
      actual = actual->next;
    }
    actual->next = nuevo;
    trip->totalLength += flyLength(actual, nuevo);
  }
}

void airTripAddBest(struct airTrip *trip, char *name, float longitude,float latitude) {
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
  correcto = actual;
  while (actual->next != NULL) {

    length2 = flyLength(actual, nuevo) + flyLength(nuevo, actual->next);

    if (length2 < length1) {
      correcto = actual;
    }
    if (strCmp(nuevo->name, actual->name) == 0){
      correcto = actual;
      break;
    }
    
    actual = actual->next;
  }
  
  if (trip->totalLength + flyLength(actual, nuevo) < trip->totalLength + length2 - flyLength(correcto, correcto->next)){
    correcto = actual;
  }
  if (trip->totalLength + flyLength(trip->first, nuevo) + flyLength(nuevo, trip->first->next) - flyLength(trip->first, trip->first->next) < trip->totalLength + flyLength(actual, nuevo)){
    correcto = trip->first;
  }
  
  
  // Si la longitud del vuelo es menor, entonces agregamos el nuevo aeropuerto
  // entre el aeropuerto actual y el siguiente
  if (correcto->next == NULL){
    correcto->next = nuevo;
    trip->totalLength += flyLength(correcto, nuevo);
  }else{
    nuevo->next = correcto->next;
    correcto->next = nuevo;
    trip->totalLength = trip->totalLength + flyLength(correcto, nuevo) + flyLength(nuevo, nuevo->next) - flyLength(correcto, nuevo->next);
  }
}


void airTripJoin(struct airTrip **tripJoin, struct airTrip *trip1,
                 struct airTrip *trip2) {

  /*
   Consigna: Une dos recorridos borrando los recorridos pasados por parámetro y
   retornando un nuevo recorrido en el doble puntero. Los recorridos serán
   unidos directamente colocando todas las paradas del trip1 y luego todas las
   paradas del trip2. Si el nombre del avión en ambos recorridos es el mismo,
   entonces se dejará solo este nombre. Si los nombres son diferentes, se deberá
   construir una nueva string que concatene el nombre del primero con el nombre
   del segundo separados por un guión. Por ejemplo, si el avión era un
   "Boeing737" para un recorrido y "Boeing747" para el otro, el nombre
   resultante será "Boeing737-Boeing747"
   */
  struct airTrip *nuevo = (struct airTrip *)malloc(sizeof(struct airTrip)); // struct airTrip* guarda el nuevo recorrido
  nuevo->plane = strDup(trip1->plane); // Aca se copia el nombre del avion del primer recorrido en el nuevo recorrido
  nuevo->totalLength = trip1->totalLength + trip2->totalLength; // Aca se calcula la longitud total del nuevo recorrido
  nuevo->first = trip1->first; // Aca se copia el primer aeropuerto del primer recorrido en el nuevo recorrido
  struct airport *actual = trip1->first; // struct airport* guarda el aeropuerto actual
  while (actual->next != NULL) { // Mientras el aeropuerto actual no sea el ultimo de la lista
    actual = actual->next; // El aeropuerto actual pasa a ser el aeropuerto siguiente al actual
  }
  nuevo->totalLength += flyLength(actual, trip2->first);
  actual->next = trip2->first; // El aeropuerto siguiente al actual pasa a ser el primer aeropuerto del segundo recorrido
  if (strCmp(trip1->plane, trip2->plane) !=0) { // Si el nombre del avion del primer recorrido es distinto al nombre del avion del segundo recorrido
    nuevo->plane = strCnt(nuevo->plane,"-"); // Aca se agrega un guion al nombre del avion del nuevo recorrido
    nuevo->plane = strCnt(nuevo->plane,trip2->plane); // Aca se agrega el nombre del avion del segundo recorrido al nombre del avion del nuevo recorrido
  }
  free(trip1);       // Se libera el primer recorrido
  free(trip2);       // Se libera el segundo recorrido
  *tripJoin = nuevo; // El doble puntero tripJoin pasa a ser el nuevo recorrido
}

void airTripDelLast(struct airTrip *trip) {

  /*
Consigna: Borra la última parada de un recorrido. Para esto debe liberar la
memoria, tanto del nodo como del string del nombre
*/
  struct airport *actual = trip->first; // struct airport* guarda el aeropuerto actual
  struct airport *anterior = NULL; // struct airport* guarda el aeropuerto anterior al aeropuerto actual
  while (actual->next != NULL) { // Mientras el aeropuerto actual no sea el ultimo de la lista
    anterior = actual;     // El aeropuerto anterior al actual pasa a ser el aeropuerto actual
    actual = actual->next; // El aeropuerto actual pasa a ser el aeropuerto siguiente al actual

  }
  trip->totalLength = trip->totalLength - flyLength(anterior, actual);
  free(actual->name);    // Se libera el nombre del aeropuerto actual
  free(actual);          // Se libera el aeropuerto actual
  anterior->next = NULL; // El aeropuerto siguiente al anterior pasa a ser NULL

}

void airTripRemoveDuplicates(struct airTrip* trip) {
 
 // Consigna: Borra todas las paradas duplicadas dentro de un recorrido, dejando solo la primer aparición de cada una
  
  struct airport* actual = trip->first; // struct airport* guarda el aeropuerto actual
  struct airport* eliminar; // struct airport* guarda el aeropuerto anterior al aeropuerto actual
  struct airport* siguiente; // struct airport* guarda el aeropuerto siguiente al aeropuerto actual
  trip->totalLength = 0;
  while (actual->next != NULL){ // Mientras el aeropuerto actual no sea NULL
    siguiente = actual->next; // El aeropuerto siguiente al actual pasa a ser el aeropuerto siguiente al actual
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

  /*
Consigna: Retorna una string con los nombres de todas las paradas del recorrido
separadas por un guión. Si le paso un recorrido con paradas A B C D E, retorna
"A-B-C-D-E"
*/
  
  char* viaje = (char*)malloc(sizeof(char)); // Creamos el string

  if (trip == NULL){// Caso vacio
    return viaje;
  }
  struct airport* actual = trip->first;
  viaje = strCnt(viaje, actual->name);
  while (actual->next != NULL){ // Recorre los aeropuertos concatenandolos al string
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
