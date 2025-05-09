#ifndef MATICE_H_INCLUDED
#define MATICE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    double **prvek;
    int radku, sloupcu;
} Tmatice;

Tmatice * novaMatice(int r, int s);

void uvolniMatici(Tmatice *m);

Tmatice * nactiMatici(FILE *in);

void tiskniMatici(FILE *out, Tmatice *m);

void prohodRadky(Tmatice *m, int r1, int r2);

void nahodnaMatice(Tmatice* m);

#endif // matice_H_GUARD
