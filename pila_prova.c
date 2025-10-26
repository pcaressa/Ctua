// pila_prova.c

#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

// Aspetta fino a che nun se preme invio.
void aspetta(void) {
    char buffer[8];
    fgets(buffer, sizeof buffer, stdin);
}

int main(void) {
    Pila pila;

    puts("\n\nPrima prova: pila de stringhe.");
    pila = pila_daje();
    for (int i = 0; i < 20; ++ i)
        pila_spigni(pila, "Stocazzo!");
    printf("La pila de stringhe contiene %zu robbe\n",
        pila_lunghezza(pila));
    puts("Mo stampo er contenuto... 'O sai chi te saluta tanto?");
    aspetta();
    while (pila_lunghezza(pila) > 0)
        puts(pila_pija(pila));
    pila_levetedarcazzo(pila);

    puts("\n\nSeconda prova: pila de pile (mica cazzo).");
    pila = pila_daje();
    pila_spigni(pila, NULL);
    for (int i = 0; i < 100; ++ i)
        pila_spigni(pila, pila);
    printf("La pila de pile contiene %zu robbe\n",
        pila_lunghezza(pila));
    puts("Mo stampo er contenuto (aho, so' indirizzi de memoria).");
    aspetta();
    while (pila_lunghezza(pila) > 0)
        printf("%p ", pila_pija(pila));
    pila_levetedarcazzo(pila);

    puts("\n\nTerza prova: pila de nummeri conzecutivi.");
    union { double x; void *p; } nummero;
    pila = pila_daje();
    for (int i = 0; i < 1000; ++ i) {
        nummero.x = i;
        pila_spigni(pila, nummero.p);
    }
    printf("La pila de pile contiene %zu robbe\n",
           pila_lunghezza(pila));
    puts("Mo stampo er contenuto da'a cima ar fonno.");
    aspetta();
    for (int i = 0; i < pila_lunghezza(pila); ++ i) {
        nummero.p = pila_ennesimo(pila, i);
        printf("%g ", nummero.x );
    }
    puts("\nMo stampo er contenuto dar fonno a'a cima.");
    aspetta();
    for (int i = pila_lunghezza(pila) - 1; i >= 0; -- i) {
        nummero.p = pila_ennesimo(pila, i);
        printf("%g ", nummero.x);
    }
    pila_levetedarcazzo(pila);
    
    puts("\nSe lo semo visto.");
    return 0;
}
