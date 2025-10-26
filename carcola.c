// carcola.c

// Implementazzione da'a classe carcola.

#include <assert.h> // assert
#include <math.h>   // pow
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carcola.h"
#include "pila.h"

// Ce servono elementi che so' puntatori o nummeri.
typedef union {double n; void *p;} Elemento;

/* 'N carcolo viene compilato drento 'n vettore codice, che ppoi
   è 'na pila che scandimo dar fonno fino in cima. Pe' fallo,
   usamo la funzzione pila_ennesimo, che ppero' punta a un
   elemento 'na'a pila partendo dalla cima. Pe' questo er
   valore inizziale de pc è lunghezza, in modo che a'inizzio
   punta all'elemento 'n fonno a'a codice, poi 'o decrementamo
   ffino a quando diventa zzero e, a quer punto, stamio
   all'urtimo elemento de codice. Pe' questo motivo pc è
   n'intero co' segno, anfatti quanno è meno uno amio finito.
   A pila invece contiene 'li valori temporanei der carcolo e er
   risurtato finale. */
struct carcola_s {
    Pila pila;      // contiene 'li valori temporanei.
    Pila codice;    // contiene 'e funzzioni da esegui'.
    int pc;         // usato pe' scandi' codice.
};

// Eccezzione.
jmp_buf carcola_nu_rompe;

// ATTRIBBUTI PRIVATI

// Mandrakata pe' risparmia' spazio e pazzienza.
#define DEFUN(nome, istruzzione)    \
static void nome(Carcola c) {       \
    Elemento e1, e2;                \
    e2.p = pila_pija(c->pila);      \
    e1.p = pila_pija(c->pila);      \
    istruzzione;                    \
    pila_spigni(c->pila, e1.p);     \
}

// Funzzioni che imprementano l'operazzioni aritmmetiche.
DEFUN(ADDIZZIONE, e1.n += e2.n)
DEFUN(SOTTRAZZIONE, e1.n -= e2.n)
DEFUN(MORTIPRICAZZIONE, e1.n *= e2.n)
DEFUN(DIVISIONE, e1.n /= e2.n)
DEFUN(POTENZA, e1.n = pow(e1.n,e2.n))

static void NEGAZZIONE(Carcola c) {
    Elemento e;
    e.p = pila_pija(c->pila);
    e.n = -e.n;
    pila_spigni(c->pila, e.p);
}

/* Pija l'elemento seguente ner vettore carcolo->codice[]
   e 'o spigne su'a pila. */
static void NUMMERO(Carcola c) {
    -- c->pc;
    assert(c->pc >= 0); // Si nun succede è 'n bugghe.
    pila_spigni(c->pila, pila_ennesimo(c->codice, c->pc));
}

// Tabella d'o'operatori.
static struct {
    char opperatore;
    int priorita;
    void (*funzzione)(Carcola);
} OPPERATORI[] = {
    {'+', 1, ADDIZZIONE},
    {'-', 1, SOTTRAZZIONE},
    {'*', 2, MORTIPRICAZZIONE},
    {'/', 2, DIVISIONE},
    {'-', 3, NEGAZZIONE},
    {'^', 4, POTENZA},
};

// METODI PRIVATI

/* Torna l'indice de l'elemento de OPPERATORI dato er nome.
   Si' nu' lo trova, torna -1. */
static int carcola_cerca_opperatore(int opperatore) {
    for (int i = 0; i < sizeof(OPPERATORI)/sizeof(*OPPERATORI); ++ i)
        if (OPPERATORI[i].opperatore == opperatore)
            return i;
    return -1;
}

// Torna 'a priorità de 'n'opperatore data la sua funzzione.
static int carcola_priorita(void *funzzione) {
    for (int i = 0; i < sizeof(OPPERATORI)/sizeof(*OPPERATORI); ++ i)
        if (OPPERATORI[i].funzzione == funzzione)
            return OPPERATORI[i].priorita;
    assert(!"Bacarozzo, li mortacci tua!");
}

/* Parsa 'n'espressione da e, drento er codice de c ffino a che
   nun trova 'a fine de'espressione o 'na parentesi chiusa.
   Ritorna er valore aggiornato de e. */
static char *carcola_parsa(Carcola c, char *e) {
    /* Pe' parsa' 'a stringa, usamo er metodo bottome-uppe ca'a
       precedenza do'opperatori. Ce serve 'na pila indove
       memorizza' l'opperatori. */
    Pila opperatori = pila_daje();
    while (*e != '\0' && *(e += strspn(e, " \n\r\t\v")) != '\0') {
        // M'aspetto n'opperando: -x, (x) o 'n nummero.
        if (*e == '-') {
            pila_spigni(opperatori, NEGAZZIONE);
            ++ e;       // sarta er meno.
            continue;   // mo s'aspettamo 'n'opperando.
        }
        if (*e == '(') {
            e = carcola_parsa(c, e + 1);
            if (*e != ')') break;   // erore, nun so' cazzi nostra.
            ++ e;       // sarta 'a parentesi si la trova.
        } else {
            // Qua dev'esse' 'n nummero.
            char *doppo;
            Elemento nummero;
            nummero.n = strtod(e, &doppo);
            if (doppo == e) break; // er chiamante se becca l'erore
            e = doppo;
            // A rantaime spignemo er nummero su'a pila.
            pila_spigni(c->codice, NUMMERO);
            pila_spigni(c->codice, nummero.p);
        }
        // Si c'è 'n'opperatore lo compilamo, sinno uscimo.
        e += strspn(e, " \n\r\t\v");    // sarta spazzi.
        int i = carcola_cerca_opperatore(*e);
        if (i < 0) break;   // ffine dell'espressione.
        ++ e;   // sarta l'opperatore.
        
        /* Si l'opperatore ha priorità maggiore de queli su'a pila,
           'li compila tutti. Poi in ogno caso spigne l'operatore
           su'a' pila. */
        while (pila_lunghezza(opperatori) > 0
        && carcola_priorita(pila_cima(opperatori)) >= OPPERATORI[i].priorita)
            pila_spigni(c->codice, pila_pija(opperatori));
            
        pila_spigni(opperatori, OPPERATORI[i].funzzione);
    }
    // Si ce stanno opperatori na'a pila, 'li compila tutti.
    while (pila_lunghezza(opperatori) > 0)
        pila_spigni(c->codice, pila_pija(opperatori));
    pila_levetedarcazzo(opperatori);
    return e;
}

// METODI PUBBLICI

Carcola carcola_daje(char *che_dovemo_da_fa) {
    // Crea 'o'oggetto.
    Carcola c = malloc(sizeof(struct carcola_s));
    if (c == NULL) {
        puts("Aho famme ggira' su un compiute serio! Nun ce sta più memoria!");
        longjmp(carcola_nu_rompe, 1);
    }
    // Inizzializza 'o'oggetto.
    c->pc = 0;
    c->codice = pila_daje();
    c->pila = pila_daje();
    char *fine = carcola_parsa(c, che_dovemo_da_fa);
    if (*fine != '\n' && *fine != '\0') {
        puts("Manco 'n'espressione sei bbono a scrive'!");
        longjmp(carcola_nu_rompe, 2);
    }
    return c;
}

void carcola_levetedarcazzo(Carcola c) {
    if (c != NULL) {
        pila_levetedarcazzo(c->codice);
        pila_levetedarcazzo(c->pila);
        free(c);
    }
}

double carcola_risponni(Carcola c) {
    assert(c != NULL);
    for (c->pc = pila_lunghezza(c->codice) - 1; c->pc >= 0 ; -- c->pc) {
        void (*funzzione)(Carcola) = pila_ennesimo(c->codice, c->pc);
        (*funzzione)(c);
    }
    if (pila_lunghezza(c->pila) != 1) {
        puts("Ce sta un cazzo de erore, sicuramente corpa tua!!!");
        longjmp(carcola_nu_rompe, 3);
    }
    Elemento e;
    e.p = pila_pija(c->pila);
    return e.n;
}

