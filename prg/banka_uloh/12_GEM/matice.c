/* Modul pro práci s maticemi.
 *
 * Copyright (c) David Martinek, 2018--2024
 */

#include "matice.h"
#include "matice.h"
#include<stdlib.h>
#include<stdio.h>

Tmatice * novaMatice(int r, int s)
{
    Tmatice* matice = malloc(sizeof(Tmatice));

    if (matice == NULL) {
        return NULL;
    }

    matice->radku = r;
    matice->sloupcu = s;
    matice->prvek = malloc(r * sizeof(double*));

    if (matice->prvek == NULL) {
        free(matice);
        return NULL;
    }

    for (int i = 0; i < r; i++) {
        matice->prvek[i] = malloc(s * sizeof(double));
        if (matice->prvek[i] == NULL) {
            matice->radku = i;
            uvolniMatici(matice);
            return NULL;
        }
    }

    return matice;
}

void uvolniMatici(Tmatice *m)
{
    for (int i = 0; i < m->radku; i++) {
        free(m->prvek[i]);
    }

    free(m->prvek);
    free(m);
}

Tmatice * nactiMatici(FILE *in)
{
    int r;
    int s;
    if (fscanf(in, "%d %d", &r, &s) != 2) {
        return NULL;
    }

    double number;

    Tmatice* m = novaMatice(r, s);
    if (m == NULL) {
        return NULL;
    }
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < s; j++) {
            if (fscanf(in, "%f", &number) != 1) {
                uvolniMatici(m);
                return NULL;
            }
            m->prvek[i][j] = number; 
        }
    }

    return m;
}

void tiskniMatici(FILE *out, Tmatice *m)
{
     for (int i = 0; i < m->radku; i++) {
        for (int j = 0; j < m->sloupcu; j++) {
            fprintf(out, "%f ", m->prvek[i][j]);
        }
        fprintf(out, "\n");
    } 
}

void prohodRadky(Tmatice *m, int r1, int r2)
{
    double* radek = m->prvek[r1];
    m->prvek[r1] = m->prvek[r2];
    m->prvek[r2] = radek;
}

void nahodnaMatice(Tmatice* m)
{
  for (int r = 0; r < m->radku ; ++r)
  {
    for (int s = 0; s < m->sloupcu ; ++s)
    {
      {
        m->prvek[r][s] = (double)((rand()%2000)-1000) / 100;
      }
    }
  }
}

