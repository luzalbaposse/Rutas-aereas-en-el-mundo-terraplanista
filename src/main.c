#include <stdio.h>
#include <stdlib.h>
#include "airTrip.h"

int main() {

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
    char* str3 = strDup("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789!@#$%^&*()_+-=[]{}|;':\",./<>?");
    printf("strDup(\"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789!@#$%^&*()_+-=[]{}|;':\",./<>?\") -> \"%s\"\n", str3);
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

    //airTripAddLast - Casos
    // Creo un nuevo trip para este caso de test
    struct airTrip* CasoAddLast = airTripNew("A1234");
    // Agregar una parada a un recorrido vacío
    airTripAddLast(CasoAddLast, "P01", 1.0, 1.0);
    airTripPrint(CasoAddLast);
    // printeo para ver que se agrego la parada P01 a un recorrido vacio
    printf("Se agrego la parada P01 a un recorrido vacio\n");
    printf("\n");

    // Agregar una parada a un recorrido de una sola parada
    airTripAddLast(CasoAddLast, "P02", 5.0, 5.0);
    airTripPrint(CasoAddLast);
    // printeo para ver que se agrego la parada P02 a un recorrido de una sola parada
    printf("Se agrego la parada P02 a un recorrido de una sola parada\n ");

    // Agregar una parada a un recorrido de más de una parada
    airTripAddLast(CasoAddLast, "P03", 3.0, 3.0);
    airTripPrint(CasoAddLast);
    // printeo para ver que se agrego la parada P03 a un recorrido de mas de una parada
    printf("Se agrego la parada P03 a un recorrido de mas de una parada\n");
    printf("\n");

    // Casos - airTripAddBest
    //Creo un nuevo trip para este caso de test
    struct airTrip* CasoAddBest = airTripNew("A5678");
    // Caso en que se pide agregar una parada a un recorrido vacío
    airTripAddBest(CasoAddBest, "P01", 1.0, 1.0);
    // Caso en que se pide agregar una parada a un recorrido de una sola parada
    airTripAddBest(CasoAddBest, "P02", 6.0, 7.0);
    //Caso en que se pide agregar una parada a un recorrido de más de una parada tal que la parada quede en último lugar
    airTripAddBest(CasoAddBest, "P03", 3.0, 3.0);
    // Caso en que se pide agregar una parada a un recorrido de más de una parada tal que la parada quede en segundo lugar
    airTripAddBest(CasoAddBest, "P02", 2.0, 2.0);
    // Caso en que se pide agregar una parada a un recorrido de más de una parada de tal manera que la parada quede en tercer lugar
    airTripAddBest(CasoAddBest, "P03", 2.5, 2.9);

// Casos - airTripJoin
    // Creo nuevos trips para este caso de test
    struct airTrip* CasoJoin1 = airTripNew("J1234");
    struct airTrip* CasoJoin2 = airTripNew("J5678");
    // Caso en que se pide unir dos recorridos vacíos
    airTripJoin(CasoJoin1, CasoJoin2);
    // Caso en que se pide unir un recorrido vacío con un recorrido de una sola parada
    airTripAddLast(CasoJoin2, "P01", 1.0, 1.0);
    airTripJoin(CasoJoin1, CasoJoin2);
    // Caso en que se pide unir un recorrido vacío con un recorrido de más de dos paradas cada uno
    airTripAddLast(CasoJoin2, "P02", 2.0, 2.0);
    airTripAddLast(CasoJoin2, "P03", 3.0, 3.0);
    airTripAddLast(CasoJoin1, "P01", 1.0, 1.0);
    airTripAddLast(CasoJoin1, "P02", 8.00, 2.0);
    airTripAddLast(CasoJoin1, "P03", 3.0, 3.0);
    airTripJoin(CasoJoin1, CasoJoin2);
    // Caso en que se pide unir un recorrido vacio con otro de una sola parada
    // Creo nuevos recorridos para este caso de test
    struct airTrip* CasoJoin3 = airTripNew("J9102");
    


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


    