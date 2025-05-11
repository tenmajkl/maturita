/* Modul pro práci s maticemi.
 *
 * Copyright (c) David Martinek, 2018--2024
 */

#include "matice.h"
#include "matice.h"
#include <math.h>
#include <stdbool.h>
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
            if (fscanf(in, "%lf", &number) != 1) {
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

/** \brief Vrátí index řádku s pivotem.
 *
 * Poznámka: Použij funkci fabs pro práci s absolutní hodnotou.
 *
 * \param m Tmatice* Ukazatel na rozšířenou matici soustavy.
 * \param r int Index referenčního řádku (a sloupce)
 * \return int Index řádku s pivotem.
 *
 */
int maxAbsPivot(Tmatice *m, int r)
{
    int max_r = r;
    float max = fabs(m->prvek[r][r]);
    for (int i = r + 1; i < m->radku; i++) {
        if (fabs(m->prvek[i][r]) > max) {
            max = fabs(m->prvek[i][r]);
            max_r = i;
        }
    }

    return max_r;
}

void kombinace(Tmatice* m, int r, int k, float c)
{
    for (int i = r; i < m->sloupcu; i++) {
        m->prvek[k][i] = m->prvek[r][i] * c - m->prvek[k][i];
    }
}

void radkoveUpravy(Tmatice* m, int r)
{
    for (int i = r + 1; i < m->radku; i++) {
        float c = m->prvek[i][r] / m->prvek[r][r];
        kombinace(m, r, i, c);
    }
}


/** \brief Provede přímý chod GEM.
 *
 * Změní vstupní matici na ekvivalentní horní trojúhelníkovou matici. Využije
 * přitom pivotování a ekvivalentních úprav.
 *
 * Poznámka: Vytvoř si samostatnou funkci pro pivotování a samostatnou funkci
 * pro aplikaci ekvivalentních úprav (nulování prvků pod diagonálním prvkem),
 * které zde zavoláš.
 *
 * \param m Tmatice* Ukazatel na rozšířenou matici soustavy.
 * \return int Vrací kód chyby.
 */
int gemPrimy(Tmatice *m)
{
    for (int r = 0; r < m->radku; r++) {
        int max = maxAbsPivot(m, r);
        if (m->prvek[max][r] == 0) {
            return 1;
        }
        prohodRadky(m, r, max);

        radkoveUpravy(m, r);
    }

    return 1;
}

void gemZpetny(Tmatice *m)
{
    for (int r = m->radku - 1; r >= 0; r--) {
        for (int s = r + 1; s < m->sloupcu - 1; s++) {
            m->prvek[r][m->sloupcu - 1] -= m->prvek[r][s] * m->prvek[s][m->sloupcu - 1];
        }
        m->prvek[r][m->sloupcu - 1] /= m->prvek[r][r];
    }
}

void vyresSoustavu(Tmatice *mat) 
{
    gemPrimy(mat);
    gemZpetny(mat);
}
