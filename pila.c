// pila.c

// 'Na possibile implementazzione pe' pila.h.

/*  Implementa 'na pila come n'arrei de lunghezza inizziale N:
    si se riempie lo allarga de antri N elementi, si nun ce
    riesce, chiude tutto e te sfancula. */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

#define N (32)

struct pila_s {
    void **robba;
    size_t taja;        // quanto po' contene' l'arrei robba.
    size_t lunghezza;   // quanta robba ora ce sta drento.
}

// Messaggi d'erore.
#define PILA_FORI "Hai pisciato fori dal vaso..."
#define PILA_STRARIPA "A micragnoso!!! Comprete ppiù RAM..."
#define PILA_VOTAAAAA "A cojone!!! La pila è vota!!!"

static pila_erore(const char *erore) {
    puts(erore);
    exit(1);
}

Pila pila_daje(void) {
    Pila pila = malloc(sizeof(struct pila_s));
    if (pila == NULL || (pila->robba = malloc(N*sizeof(void*))) == NULL)
        pila_erore(PILA_STRARIPA);
    pila->taja = N;
    pila->lunghezza = 0;
    return pila;
}

void pila_levetedarcazzo(Pila pila) {
    assert(pila != NULL);   // A cojone! Ce sta 'n bugghe.
    free(pila->robba);
    free(pila);
}

size_t pila_lunghezza(Pila pila) {
    assert(pila != NULL);   // A cojone! Ce sta 'n bugghe.
    return pila->lunghezza;
}

Pila pila_spigni(Pila pila, void *robba) {
    assert(pila != NULL);   // A cojone! Ce sta 'n bugghe.
    if (pila->lunghezza == pila->taja) {
        // Ingrandimo de N la pila.
        if ((pila->robba = realloc(pila->robba, (pila->taja + N)*sizeof(void*))) == NULL)
            pila_erore(PILA_STRARIPA);
        pila->taja += N;
    }
    pila->robba[pila->lunghezza++] = robba;
    return pila;
}

void *pila_pija(Pila pila) {
    assert(pila != NULL);   // A cojone! Ce sta 'n bugghe.
    if (pila->lunghezza == 0)
        pila_erore(PILA_VOTAAAAA);
    return pila->robba[--pila->lunghezza];
}

void *pila_cima(Pila pila) {
    assert(pila != NULL);   // A cojone! Ce sta 'n bugghe.
    if (pila->lunghezza == 0)
        pila_erore(PILA_VOTAAAAA);
    return pila->robba[pila->lunghezza-1];
}

void *pila_ennesimo(Pila pila, unsigned n) {
    assert(pila != NULL);   // A cojone! Ce sta 'n bugghe.
    if (n >= pila->lunghezza)
        pila_erore(PILA_FORI);
    return pila->robba[pila->lunghezza - 1 - n];
}
