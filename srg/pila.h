// pila.h

/*
    Esempio programmazzione a oggetti in C: interfacciadacazzo
    de 'na classe pe' usa' pile de robba quarziasi.
    
    Cose da sape':
    
    - si a 'na funzzione che richiede 'na pila je passsate
      NULL, so' cazzi vostra, nun ce posso fa' gnente.
    - 'a ggestione de'erori e' da regazzini, er programma se
      'nterompe co'n messaggio d'erore. Se po' ffa' de mejo
      ma lo famo n'antra vorta.
*/

#ifndef GIA_CE_STA_PILA_H
#define GIA_CE_STA_PILA_H

#include <stdlib.h>

// Com'è fatta 'na pila nun so' cazzi tua.
typedef struct pila_s *Pila;

// Crea 'na nova pila vota.
extern Pila pila_daje(void);

// Sfancula 'na pila che ggià esiste.
extern void pila_levetedarcazzo(Pila pila);

// Torna er nummero de robba nella pila.
extern size_t pila_lunghezza(Pila pila);

// Spigne 'n valore drento 'na pila.
extern Pila pila_spigni(Pila pila, void *robba);

// Toglie 'n valore da 'na pila.
extern void *pila_pija(Pila pila);

// Torna 'a robba 'n cima a'a pila.
extern void *pila_cima(Pila pila);

/* Torna l'elemento che sta n vorte sotto 'a cima da'a
   pila (si n è zero, torna proppio 'a cima). */
extern void *pila_ennesimo(Pila pila, unsigned n);

#endif // GIA_CE_STA_PILA_H
