#include <stdio.h>
#include <stdlib.h>
#include "airTrip.h"

int main() {

    // COMPLETAR

    // A Continuacion dejamos algunos ejemplos de como
    // llama a las funciones pedidas. Este codigo debe
    // ser borrado / modificado.


    // strDuplicate
    char* dup = strDup("hola");
    printf("strDup(\"hola\") -> \"%s\"\n", dup);
    free(dup);
    printf("\n");

    // strCompare
    printf("strCmp(\"abc\",\"abc\") -> %i\n", strCmp("abc","abc"));
    printf("strCmp(\"abcd\",\"abc\") -> %i\n", strCmp("abcd","abc"));
    printf("strCmp(\"abc\",\"abcd\") -> %i\n", strCmp("abc","abcd"));
    printf("\n");

    // strConcatenate
    char* concat = strCnt("123","456");
    printf("strConcatenate(\"123\",\"456\") -> \"%s\"\n", concat);
    free(concat);
    printf("\n");

    // flyLength
    struct airport a1;
    struct airport a2;
    a1.name = "a1";
    a1.latitude = 1.0;
    a1.longitude = 1.0;
    a1.next = 0;
    a2.name = "a2";
    a2.latitude = 2.0;
    a2.longitude = 2.0;
    a2.next = 0;
    float len = flyLength(&a1, &a2);
    printf("Len %f\n\n",len);

    // airTripNew
    struct airTrip* trip = airTripNew("R1234");

    // airTripAddLast
    airTripAddLast(trip, "Ra1", 1.0, 1.0);
    airTripAddLast(trip, "Ra2", 2.0, 2.0);
    airTripAddLast(trip, "Ra3", 3.0, 3.0);

    // airTripPrint
    airTripPrint(trip);
    printf("\n");

    // airTripAddBest
    airTripAddBest(trip, "P01", 1.5, 1.5);
    airTripAddBest(trip, "P02", 2.5, 2.5);
    airTripAddBest(trip, "P03", 3.5, 3.5);
    airTripAddBest(trip, "P00", 0.5, 0.5);
    airTripPrint(trip);
    printf("\n");

    // airTripJoin
    struct airTrip* tripJoin;
    struct airTrip* trip1 = airTripNew("R1234");
    airTripAddLast(trip1, "Ra1", 1.0, 1.0);
    struct airTrip* trip2 = airTripNew("R1234");
    airTripAddLast(trip2, "Ra2", 2.0, 2.0);
    airTripJoin(&tripJoin, trip1, trip2);
    airTripPrint(tripJoin);
    printf("\n");

    // airTripDelLast
    airTripDelLast(trip);
    airTripDelLast(trip);
    airTripDelLast(trip);
    airTripDelLast(trip);
    airTripPrint(trip);
    printf("\n");


    // airTripRemoveDuplicates
    airTripAddLast(trip, "T01", 10.0, 10.0);
    airTripAddLast(trip, "T02", 99.0, 99.0);
    airTripAddLast(trip, "T01", 10.0, 10.0);
    airTripAddLast(trip, "T02", 99.0, 99.0);
    airTripAddBest(trip, "T01", 10.0, 10.0);
    airTripAddBest(trip, "T02", 99.0, 99.0);
    airTripAddBest(trip, "T01", 10.0, 10.0);
    airTripAddBest(trip, "T02", 99.0, 99.0);
    airTripPrint(trip);
    airTripRemoveDuplicates(trip);
    airTripPrint(trip);
    printf("\n");

    // airTripGetTrip
    char* t = airTripGetTrip(trip);
    printf("%s\n",t);
    free(t);

    // airTripDelete
    airTripDelete(trip);
    airTripDelete(tripJoin);
    
    return 0;
}
