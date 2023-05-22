#include <stdio.h>
#include <stdlib.h>
#include "airTrip.h"

int main() {

    // strDup - Casos
    // String vacío
    printf("👀 Acá comienzan los casos de strDup\n");
    char* str1 = strDup("");
    printf("strDup(\"\") -> \"%s\"\n", str1);
    free(str1);

    // String con un caracter
    char* str2 = strDup("a");
    printf("strDup(\"a\") -> \"%s\"\n", str2);
    free(str2);

    // String que incluya todos los caracteres válidos distintos de cero
    char* str3 = strDup("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789!@#$^&*()_+-=[]{}|;':\",./<>?");
    printf("strDup(\"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789!@#$^&*()_+-=[]{}|;':\",./<>?\") -> \"%s\"\n", str3);
    free(str3);

    // strCmp - Casos
    printf("👀 Acá comienzan los casos de strCmp\n");

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
    printf("👀 Acá comienzan los casos de strCnt\n");
    char* str4 = strCnt("","abc");
    printf("strCnt(\"\",\"abc\") -> \"%s\"\n", str4);
    free(str4);

    // Un string de 3 caracteres y un string vacio
    char* str5 = strCnt("abc","");
    printf("strCnt(\"abc\",\"\") -> \"%s\"\n", str5);
    free(str5);

    //Dos strings de 1 caracter
    char* str6 = strCnt("a","b");
    printf("strCnt(\"a\",\"b\") -> \"%s\"\n", str6);
    free(str6);

    //Dos strings de 5 caracteres
    char* str7 = strCnt("abcde","fghij");
    printf("strCnt(\"abcde\",\"fghij\") -> \"%s\"\n", str7);
    free(str7);
 
    //airTripAddLast - Casos
    printf("👀 Acá comienzan los casos de airTripAddLast\n");
    // Creo un nuevo trip para este caso de test
    struct airTrip* CasoAddLast = airTripNew("A1234");
    // Agregar una parada a un recorrido vacío
    airTripAddLast(CasoAddLast, "P01", 1.0, 1.0);
    airTripPrint(CasoAddLast);
    // printeo para ver que se agrego la parada P01 a un recorrido vacio
    printf("Se agregó la parada P01 a un recorrido vacio\n");
    printf("\n");

    // Agregar una parada a un recorrido de una sola parada
    airTripAddLast(CasoAddLast, "P02", 5.0, 5.0);
    airTripPrint(CasoAddLast);
    // printeo para ver que se agrego la parada P02 a un recorrido de una sola parada
    printf("Se agregó la parada P02 a un recorrido de una sola parada\n ");

    // Agregar una parada a un recorrido de más de una parada
    airTripAddLast(CasoAddLast, "P03", 3.0, 3.0);
    airTripPrint(CasoAddLast);
    // printeo para ver que se agrego la parada P03 a un recorrido de mas de una parada
    printf("Se agregó la parada P03 a un recorrido de mas de una parada\n");
    printf("\n");

    //Libero la memoria utilizada para estos casos de test 
    airTripDelete(CasoAddLast);


    // Casos - airTripAddBest
    printf("👀 Acá comienzan los casos de airTripAddBest\n");
    //Creo un nuevo trip para este caso de test
    struct airTrip* CasoAddBest = airTripNew("A5678");
    // Caso en que se pide agregar una parada a un recorrido vacío
    airTripAddBest(CasoAddBest, "P01", 1.0, 1.0);
    printf("Se agregó la parada P01 a un recorrido vacio\n");
    airTripPrint(CasoAddBest);
    // Caso en que se pide agregar una parada a un recorrido de una sola parada
    airTripAddBest(CasoAddBest, "P02", 6.0, 7.0);
    printf("Se agregó la parada P02 a un recorrido de una sola parada\n");
    airTripPrint(CasoAddBest);
    //Caso en que se pide agregar una parada a un recorrido de más de una parada tal que la parada quede en último lugar
    airTripAddBest(CasoAddBest, "P03", 3.0, 3.0);
    printf("Se agregó la parada P03 a un recorrido de más de una parada tal que la parada quede en último lugar\n");
    airTripPrint(CasoAddBest);
    // Caso en que se pide agregar una parada a un recorrido de más de una parada tal que la parada quede en segundo lugar
    airTripAddBest(CasoAddBest, "P02", 2.0, 2.0);
    printf("Se agregó la parada P02 a un recorrido de más de una parada tal que la parada quede en segundo lugar\n");
    airTripPrint(CasoAddBest);
    // Caso en que se pide agregar una parada a un recorrido de más de una parada de tal manera que la parada quede en tercer lugar
    airTripAddBest(CasoAddBest, "P03", 2.5, 2.9);
    printf("Se agregó la parada P03 a un recorrido de más de una parada de tal manera que la parada quede en tercer lugar\n");
    airTripPrint(CasoAddBest);

    airTripDelete(CasoAddBest);

// Casos - airTripJoin
    printf("👀 Acá comienzan los casos de airTripJoin\n");
    struct airTrip* tripJoin1;
    struct airTrip* trip3 = airTripNew("R1234");
    struct airTrip* trip4 = airTripNew("R4321");

    printf("--Unir dos recorridos vacios\n");
    printf("---Recorridos input:\n");
    airTripPrint(trip3);
    airTripPrint(trip4);
    airTripJoin(&tripJoin1, trip3, trip4);
    printf("---Recorrido output:\n");
    airTripPrint(tripJoin1);
    airTripDelete(tripJoin1);
    printf("\n");


    struct airTrip* tripJoin2;
    struct airTrip* trip3_1 = airTripNew("R1234");
    struct airTrip* trip4_1 = airTripNew("R4321");

    printf("--Unir dos recorridos con una sola parada cada uno\n");
    airTripAddLast(trip3_1,"T0",1.0,1.0);
    airTripAddLast(trip4_1,"P0",4.0,4.0);
    printf("---Recorridos input:\n");
    airTripPrint(trip3_1);
    airTripPrint(trip4_1);
    airTripJoin(&tripJoin2, trip3_1, trip4_1);
    printf("---Recorrido output:\n");
    airTripPrint(tripJoin2);
    airTripDelete(tripJoin2);
    printf("\n");

    struct airTrip* trip3_2 = airTripNew("R1234");
    struct airTrip* trip4_2 = airTripNew("R4321");
    airTripAddLast(trip3_2,"T0",1.0,1.0);
    airTripAddLast(trip4_2,"P0",4.0,4.0);
    struct airTrip* tripJoin3;
    printf("--Unir dos recorridos con mas de dos paradas cada uno\n");
    airTripAddLast(trip3_2,"T1",2.0,2.0);
    airTripAddLast(trip3_2,"T2",3.0,3.0);
    airTripAddLast(trip4_2,"P2",5.0,5.0);
    airTripAddLast(trip4_2,"P3",6.0,6.0);
    printf("---Recorridos input:\n");
    airTripPrint(trip3_2);
    airTripPrint(trip4_2);
    airTripJoin(&tripJoin3, trip3_2, trip4_2);
    printf("---Recorrido output:\n");
    airTripPrint(tripJoin3);
    airTripDelete(tripJoin3);
    printf("\n");

    struct airTrip* trip5 = airTripNew("R0");
    struct airTrip* trip6 = airTripNew("R1");
    struct airTrip* tripJoin4;
    airTripAddLast(trip6,"P0",1.0,1.0);
    printf("--Unir un recorrido vacio con otro de una sola parada\n");
    printf("---Recorridos input:\n");
    airTripPrint(trip5);
    airTripPrint(trip6);
    printf("\n");
    airTripJoin(&tripJoin4, trip5, trip6);
    printf("---Recorrido output:\n");
    airTripPrint(tripJoin4);
    airTripDelete(tripJoin4);
    printf("\n");

    // airTripDelLast - Casos
    printf("👀 Acá comienzan los casos de airTripDelLast\n");
    // Creo un nuevo trip para este caso de test
    struct airTrip* CasoDel1 = airTripNew("D1234");
    
    // CadoDel1 es un recorrido de más de dos paradas
    airTripAddLast(CasoDel1, "P01", 1.0, 1.0);
    airTripAddLast(CasoDel1, "P02", 2.0, 2.0);
    airTripAddLast(CasoDel1, "P03", 3.0, 3.0);
    //Borrar el último de un recorrido de mas de dos paradas
    printf("CasoDel1 es un recorrido que tiene 3 paradas\n");
    airTripDelLast(CasoDel1);
    airTripPrint(CasoDel1);
    printf("✈️ CasoDel1 ahora tiene 2 paradas");
    // Borrar el último de un recorrido de exactamente dos paradas
    airTripDelLast(CasoDel1);
    airTripPrint(CasoDel1);
    printf("✈️ CasoDel1 ahora tiene 1 parada");
    //Borrar el último de un recorrido de exactamente una parada
    airTripDelLast(CasoDel1);
    airTripPrint(CasoDel1);
    printf("✈️ CasoDel1 ahora tiene 0 paradas");
    //Borrar el útlimo de un recorrido vacio
    airTripDelLast(CasoDel1);
    airTripPrint(CasoDel1);
    printf("✈️ CasoDel1 devuelve 0 paradas");

    airTripDelete(CasoDel1);

    // airTripRemoveDuplicates - Casos
    printf("👀 Acá comienzan los casos de airTripRemoveDuplicates\n");
    // Creo un nuevo trip para este caso de test
    struct airTrip* CasoRemoveDuplicates1 = airTripNew("R1234");
    struct airTrip* CasoRemoveDuplicates2 = airTripNew("R5678");
    struct airTrip* CasoRemoveDuplicates3 = airTripNew("R9102");
    // Borrar duplicados de un recorrido sin duplicados
    airTripAddLast(CasoRemoveDuplicates1, "P01", 1.0, 1.0);
    airTripAddLast(CasoRemoveDuplicates1, "P02", 2.0, 2.0);
    airTripAddLast(CasoRemoveDuplicates1, "P03", 3.0, 3.0);
    printf("CasoRemoveDuplicates1 es un recorrido que tiene 3 paradas\n");
    airTripPrint(CasoRemoveDuplicates1);
    airTripRemoveDuplicates(CasoRemoveDuplicates1);
    printf("✈️ Se aplicó RemoveDuplicates y CasoRemoveDuplicates1 sigue teniendo 3 paradas\n");
    airTripPrint(CasoRemoveDuplicates1);

    //Borrar duplicados de un recorrido donde son todos iguales
    airTripAddLast(CasoRemoveDuplicates2, "P01", 1.0, 1.0);
    airTripAddLast(CasoRemoveDuplicates2, "P01", 1.0, 1.0);
    airTripAddLast(CasoRemoveDuplicates2, "P01", 1.0, 1.0);
    printf("CasoRemoveDuplicates2 es un recorrido que tiene 3 paradas iguales\n");
    airTripPrint(CasoRemoveDuplicates2);
    airTripRemoveDuplicates(CasoRemoveDuplicates2);
    printf("✈️ Se aplicó RemoveDuplicates y CasoRemoveDuplicates2 ahora tiene 1 parada\n");
    airTripPrint(CasoRemoveDuplicates2);

    // Borrar duplicados de un recorrido donde todos se repiten al menos una ez en cualquier orden
    airTripAddLast(CasoRemoveDuplicates3, "P01", 1.0, 1.0);
    airTripAddLast(CasoRemoveDuplicates3, "P03", 3.0, 3.0);
    airTripAddLast(CasoRemoveDuplicates3, "P01", 1.0, 1.0);
    airTripAddLast(CasoRemoveDuplicates3, "P02", 2.0, 2.0);
    airTripAddLast(CasoRemoveDuplicates3, "P04", 5.0, 2.0);
    airTripAddLast(CasoRemoveDuplicates3, "P05", 6.0, 3.0);
    airTripAddLast(CasoRemoveDuplicates3, "P02", 2.0, 2.0);
    airTripAddLast(CasoRemoveDuplicates3, "P03", 3.0, 3.0);
    airTripAddLast(CasoRemoveDuplicates3, "P04", 5.0, 2.0);
    airTripAddLast(CasoRemoveDuplicates3, "P05", 6.0, 3.0);
    printf("CasoRemoveDuplicates3 es un recorrido que tiene 10 paradas, 5 de las cuales se repiten\n");
    airTripPrint(CasoRemoveDuplicates3);
    airTripRemoveDuplicates(CasoRemoveDuplicates3);
    printf("✈️ Se aplicó RemoveDuplicates y CasoRemoveDuplicates3 ahora tiene 5 paradas\n");
    airTripPrint(CasoRemoveDuplicates3);

    airTripDelete(CasoRemoveDuplicates1);
    airTripDelete(CasoRemoveDuplicates2);
    airTripDelete(CasoRemoveDuplicates3);

    // airTripGetTrip - Casos
    printf("👀 Acá comienzan los casos de airTripGetTrip\n");
    // Creo un nuevo trip para este caso de test
    struct airTrip* CasoGetTrip1 = airTripNew("G1234");
    struct airTrip* CasoGetTrip2 = airTripNew("G5678");

    // Usar de parámetro un recorrido vacío
    printf("CasoGetTrip1 es un recorrido vacío\n");
    airTripPrint(CasoGetTrip1);
    char* vacio = airTripGetTrip(CasoGetTrip1);
    printf("✈️ Se aplicó GetTrip y CasoGetTrip1:\n");
    airTripPrint(CasoGetTrip1);
    free(vacio);
    

    //Usar de parámatro un recorrido de solo dos paradas
    airTripAddLast(CasoGetTrip2, "P01", 1.0, 1.0);
    airTripAddLast(CasoGetTrip2, "P02", 2.0, 2.0);
    printf("CasoGetTrip2 es un recorrido que tiene 2 paradas\n");
    char* t = airTripGetTrip(CasoGetTrip2);
    printf("%s\n", t);
    printf("✈️ Se aplicó GetTrip y CasoGetTrip2:\n");
    airTripPrint(CasoGetTrip2);
    free(t);
    

    // Usar de parámetro un recorrido de una sola parada
    airTripAddLast(CasoGetTrip1, "P01", 3.0, 3.0);
    printf("CasoGetTrip1 es un recorrido que tiene 1 parada\n");
    char* t1 = airTripGetTrip(CasoGetTrip1);
    printf("%s\n", t1);
    printf("✈️ Se aplicó GetTrip y CasoGetTrip1:\n");
    airTripPrint(CasoGetTrip1);
    free(t1);


    airTripDelete(CasoGetTrip1);
    airTripDelete(CasoGetTrip2);
    

    // Caso - airTripDelete
    // Creo un struct para este caso de test
    printf("👀 Acá comienzan los casos de airTripDelete\n");
    struct airTrip* CasoTripDelete = airTripNew("D1234");
    struct airTrip* CasoTripDelete2 = airTripNew("D5678");
    struct airTrip* CasoTripDelete3 = airTripNew("D1919");
    printf("CasoTripDelete es un recorrido vacío\n");
    // Borrar un recorrido vacío
    airTripDelete(CasoTripDelete);
    printf("✈️ Se aplicó Delete y CasoTripDelete se eliminó\n");
    

    // Borrar un recorrido de solo una parada
    printf("CasoTripDelete2 es un recorrido que tiene 1 parada\n");
    airTripAddLast(CasoTripDelete2, "P01", 1.0, 1.0);
    airTripDelete(CasoTripDelete2);
    printf("✈️ Se aplicó Delete y CasoTripDelete2:\n");

    //Borrar un recorrido de más de dos paradas
    airTripAddLast(CasoTripDelete3, "P01", 1.0, 1.0);
    airTripAddLast(CasoTripDelete3, "P02", 2.0, 2.0);
    airTripAddLast(CasoTripDelete3, "P03", 3.0, 3.0);
    printf("CasoTripDelete3 es un recorrido que tiene 3 paradas\n");
    airTripDelete(CasoTripDelete3);
    printf("✈️ Se aplicó Delete y CasoTripDelete3:\n");
    

    // Terminaron los casos de test! Wooooooo
    printf("🎉 Terminaron los casos de test! Wooooooo\n");
    printf("Les mandan saludos, Tommy, Tomi y Lu 🤗\n");
    
    return 0;
}
