// carcola.h

/* 'Sta classe consente de carcola' er valore de n'espressione
   che viene data ar costruttore. Si quarcosa va storto, se
   lancia n'eccezzione. */

/*
    'Sto file esporta 'na funzzione pe' parsa' 'na stringa.
    'A stringa dev'esse' fatta accusscì:

        opperando {opperatore opperando}

    indove

        opperando = nummero | "-" nummero
        opperatore = "+" | "-" | "*" | "/" | "^"

    'A rottura de cazzo è che "-" vor di' sia a differenza,
    sia a negazzione, ma a'a fine se fa.
*/

#ifndef CARCOLA_GIA_CE_STA
#define CARCOLA_GIA_CE_STA

#include <setjmp.h>

// Eccezzione usata drento 'li metodi de la classe.
extern jmp_buf carcola_nu_rompe;

// Che ce sta na'a classe nun so' cazzi tua.
typedef struct carcola_s *Carcola;

/* Costruttore: pija 'na stringa, 'a parsa e crea 'n'oggetto
   si nun ce riesce, te sfancula co' 'n'eccezzione. 'A stringa
   viene parsata ignorando 'li spazzi, e provando a parsalla come
   'na serie de opperandi separati da opperatori.

   'N'opperando po' esse un nummero, un segno meno seguito da
   n'antro opperando, n'espressione fra parentesi.

   'N'opperatore po' esse uno fra + - * / ^. */
extern Carcola carcola_daje(char *che_dovemo_da_fa);

/* Distruttore. */
extern void carcola_levetedarcazzo(Carcola c);

/* Fa' er carcolo vero e proppio e torna er risurtato. */
extern double carcola_risponni(Carcola c);

#endif // CARCOLA_GIA_CE_STA

