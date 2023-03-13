#include <stdio.h>
#include <stdlib.h>
#include "airTrip.h"

int main() {
    /*
    Consigna: Hacer casos de test para las funciones de airTrip.c
    */
    // strDup - Casos
    // String vacío
    char* str1 = strDup("");
    printf("strDup(\"\") -> \"%s\"\n", str1);
    free(str1);

    // String con un caracter
    char* str2 = strDup("a");
    printf("strDup(\"a\") -> \"%s\"\n", str2);
    free(str2);

    // String que incluya todos los caracteres válidos distintos de cero
    char* str3 = strDup("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()_+-=[]{}|;':\",./<>?");
    printf("strDup(\"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()_+-=[]{}|;':\",./<>?\") -> \"%s\"\n", str3);
    free(str3);

    // strCmp - Casos
    // Dos strings vacíos
    int cmp1 = strCmp("","");
    printf("strCmp(\"\",\"\") -> %d\n", cmp1);
    
    // Dos strings con un caracter
    int cmp2 = strCmp("a","a");
    printf("strCmp(\"a\",\"a\") -> %d\n", cmp2);

    // Strings iguales hasta un carácter ((hacer cmpStr(s1,s2) y cmpStr(s2,s1))
    int cmp3 = strCmp("abc","abcd");
    printf("strCmp(\"abc\",\"abcd\") -> %d\n", cmp3);
    int cmp4 = strCmp("abcd","abc");
    printf("strCmp(\"abcd\",\"abc\") -> %d\n", cmp4);

    // Dos strings diferentes (hacer cmpStr(s1,s2) y cmpStr(s2,s1))
    int cmp5 = strCmp("abc","abd");
    printf("strCmp(\"abc\",\"abd\") -> %d\n", cmp5);

    // strConcatenate - Casos
    // Un string vacio y un string de 3 caracteres
    char* str4 = strConcatenate("","abc");
    printf("strConcatenate(\"\",\"abc\") -> \"%s\"\n", str4);
    free(str4);

    // Un string de 3 caracteres y un string vacio
    char* str5 = strConcatenate("abc","");
    printf("strConcatenate(\"abc\",\"\") -> \"%s\"\n", str5);
    free(str5);

    //Dos strings de 1 caracter
    char* str6 = strConcatenate("a","b");
    printf("strConcatenate(\"a\",\"b\") -> \"%s\"\n", str6);
    free(str6);

    //Dos strings de 5 caracteres
    char* str7 = strConcatenate("abcde","fghij");
    printf("strConcatenate(\"abcde\",\"fghij\") -> \"%s\"\n", str7);
    free(str7);

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

    //airTripAddLast - Casos
    // Agregar una parada a un recorrido vacío
    airTripAddLast(trip, "P01", 1.0, 1.0);
    airTripPrint(trip);
    printf("\n");

    // Agregar una parada a un recorrido de una sola parada
    airTripAddLast(trip, "P02", 5.0, 5.0);
    airTripPrint(trip);
    printf("\n");

    // Agregar una parada a un recorrido de más de una parada
    airTripAddLast(trip, "P03", 3.0, 3.0);
    airTripPrint(trip);
    printf("\n");

    // airTripAddBest - Casos
    // Agregar una parada a un recorrido vacío
    airTripAddBest(trip, "P01", 1.0, 1.0);
    airTripPrint(trip);
    printf("\n");

    // Agregar una parada a un recorrido de una sola parada
    airTripAddBest(trip, "P02", 6.0, 7.0);
    airTripPrint(trip);
    printf("\n");

    // Agregar una parada a un recorrido de más de una parada tal que la parada quede en último lugar
    airTripAddBest(trip, "P03", 3.0, 3.0);
    airTripPrint(trip);
    printf("\n");

    // Agregar ua parada a un recorrido de más de una parada tal que la parada quede en segundo lugar
    airTripAddBest(trip, "P02", 2.0, 2.0);
    airTripPrint(trip);
    printf("\n");

    // Agregar una parada a un recorrido de más de una parada tal que la parada quede en tercer lugar
    airTripAddBest(trip, "P03", 2.5, 2.9);
    airTripPrint(trip);
    printf("\n");


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
/*
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
    */
    return 0;
}


    