// \file: carcolatrice.c

#include <stdio.h>
#include <setjmp.h>
#include "carcola.h"

int main(void) {
    char che_devo_da_fa[BUFSIZ] = {0};
    puts("'Na carcolatrice de 'mmerda, ma funzziona.");
    puts("Premi control D pe' usci'.");
    while (putchar('>'), fgets(che_devo_da_fa, BUFSIZ, stdin) != NULL) {
        Carcola carcolo = NULL;
        if (setjmp(carcola_nu_rompe) == 0) {
            carcolo = carcola_daje(che_devo_da_fa);
            printf("Er risurtato sarebbe %g\n", carcola_risponni(carcolo));
        } else {
            puts("Vabbe', riproceve.");
            carcola_levetedarcazzo(carcolo);
        }
    }
    puts("Se lo semo visto.");
    return 0;
}
