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
    char* str3 = strDup("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789!@#$%^&*()_+-=[]{}|;':\",./<>?");
    printf("strDup(\"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789!@#$%^&*()_+-=[]{}|;':\",./<>?\") -> \"%s\"\n", str3);
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
 
    // flyLength
    printf("👀 Este es el test ya existente de FlyLength\n");
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
    printf("👀 Acá comienzan los casos de airTripAddLast\n");
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
    printf("👀 Acá comienzan los casos de airTripAddBest\n");
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
    printf("👀 Acá comienzan los casos de airTripJoin\n");
    // Creo nuevos trips para este caso de test
    struct airTrip* CasoJoin1 = airTripNew("J1234");
    struct airTrip* CasoJoin2 = airTripNew("J5678");
    struct airTrip* Joined = airTripNew("J9012");
    struct airTrip* Joined1 = airTripNew("J9012");
    struct airTrip* Joined2 = airTripNew("J9012");
    struct airTrip* Joined3 = airTripNew("J9012");
    // Caso en que se pide unir dos recorridos vacíos
    airTripJoin(Joined, CasoJoin1, CasoJoin2);
    // Caso en que se pide unir un recorrido vacío con un recorrido de una sola parada
    airTripAddLast(CasoJoin2, "P01", 1.0, 1.0);
    airTripJoin(Joined1, CasoJoin1, CasoJoin2);
    // Caso en que se pide unir un recorrido vacío con un recorrido de más de dos paradas cada uno
    airTripAddLast(CasoJoin2, "P02", 2.0, 2.0);
    airTripAddLast(CasoJoin2, "P03", 3.0, 3.0);
    airTripAddLast(CasoJoin1, "P01", 1.0, 1.0);
    airTripAddLast(CasoJoin1, "P02", 8.00, 2.0);
    airTripAddLast(CasoJoin1, "P03", 3.0, 3.0);
    airTripJoin(Joined2, CasoJoin1, CasoJoin2);
    // Creo nuevos recorridos para este caso de test
    struct airTrip* CasoJoin3 = airTripNew("J9102");
    struct airTrip* CasoJoin4 = airTripNew("J9929");
    airTripAddLast(CasoJoin4, "P01", 8.0, 6.0);
    // Caso en que se pide unir un recorrido vacio con otro de una sola parada
    airTripJoin(Joined3, CasoJoin3, CasoJoin4);


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
    airTripRemoveDuplicates(CasoRemoveDuplicates1);

    //Borrar duplicados de un recorrido donde son todos iguales
    airTripAddLast(CasoRemoveDuplicates2, "P01", 1.0, 1.0);
    airTripAddLast(CasoRemoveDuplicates2, "P01", 1.0, 1.0);
    airTripAddLast(CasoRemoveDuplicates2, "P01", 1.0, 1.0);
    airTripRemoveDuplicates(CasoRemoveDuplicates2);

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
    airTripRemoveDuplicates(CasoRemoveDuplicates3);
    
    // airTripGetTrip - Casos
    printf("👀 Acá comienzan los casos de airTripGetTrip\n");
    // Creo un nuevo trip para este caso de test
    struct airTrip* CasoGetTrip1 = airTripNew("G1234");
    struct airTrip* CasoGetTrip2 = airTripNew("G5678");

    // Usar de parámetro un recorrido vacío
    airTripGetTrip(CasoGetTrip1);

    //Usar de parámatro un recorrido de solo dos paradas
    airTripAddLast(CasoGetTrip2, "P01", 1.0, 1.0);
    airTripAddLast(CasoGetTrip2, "P02", 2.0, 2.0);
    airTripGetTrip(CasoGetTrip2);

    // Usar de parámetro un recorrido de una sola parada
    airTripAddLast(CasoGetTrip1, "P01", 3.0, 3.0);
    airTripGetTrip(CasoGetTrip1);

    // Caso - airTripDelete
    // Creo un struct para este caso de test
    printf("👀 Acá comienzan los casos de airTripDelete\n");
    struct airTrip * CasoTripDelete = airTripNew("D1234");
    struct airTrip *CasoTripDelete2 = airTripNew("D5678");
    struct airTrip* CasoTripDelete3 = airTripNew("D1919");

    // Borrar un recorrido vacío
    airTripDelete(CasoTripDelete);

    // Borrar un recorrido de solo una parada
    airTripAddLast(CasoTripDelete2, "P01", 1.0, 1.0);
    airTripDelete(CasoTripDelete2);

    //Borrar un recorrido de más de dos paradas
    airTripAddLast(CasoTripDelete3, "P01", 1.0, 1.0);
    airTripAddLast(CasoTripDelete3, "P02", 2.0, 2.0);
    airTripAddLast(CasoTripDelete3, "P03", 3.0, 3.0);

    airTripDelete(CasoTripDelete3);
    
    return 0;
}


    