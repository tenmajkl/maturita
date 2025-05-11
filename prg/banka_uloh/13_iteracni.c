#include <math.h>
#include<stdio.h>
#include <stdbool.h>

#define MAX_MAT 50

typedef struct {
    float prvek[MAX_MAT][MAX_MAT];
    int m, n;
} TMatice;

bool nacti(FILE* vstup, TMatice* mat)
{
    if (fscanf(vstup, "%i %i", &mat->m, &mat->n) != 2) {
        return false;
    }

    if (mat->m > MAX_MAT || mat->n > MAX_MAT) {
        return false;
    }

    for (int r = 0; r < mat->m; r++) {
        for (int s = 0; s < mat->n; s++) {
            if (fscanf(vstup, "%f", &mat->prvek[r][s]) != 1) {
                return false;
            }
        }
    }

    return true;
}

bool jeRozsirenaMat(TMatice mat) {
    return mat.n == mat.m + 1;
}

bool jeDominantni(TMatice mat) {
    for (int r = 0; r < mat.m; r++) {
        float soucet = 0;
        for (int s = 0; s < mat.n - 1; s++)  {
            if (s == r) {
                continue;
            }
            soucet += fabs(mat.prvek[r][s]);
        }

        // >= protoze diagonalni musi byt ostre vetsi nez soucet, takze pokud je soucet neostre vetsi tak false
        if (soucet >= fabs(mat.prvek[r][r])) {
            return false;
        }
    }

    return true;
}

// kdyz strukturu nepredam odkazem tak ji nemuzu menit
void optimalizace(TMatice* mat)
{
    for (int r = 0; r < mat->m; r++) {
        double diag = mat->prvek[r][r];
        mat->prvek[r][r] = 0;
        for (int s = 0; s < mat->n; s++) {
            mat->prvek[r][s] /= diag;
        }
    }
}

TMatice gausSeidl(TMatice mat, float e)
{
    TMatice vystup;
    for (int i = 0; i < mat.m; i++) {
        vystup.prvek[i][0] = 0;
    }
    vystup.m = mat.m;
    vystup.n = 1;
    bool jePresny = false;
    while (!jePresny) {
        jePresny = true;
        for (int r = 0; r < mat.m; r++) {
            float suma = 0;
            for (int s = 0; s < mat.n - 1; s++) {
                suma += mat.prvek[r][s] * vystup.prvek[s][0];
            }
            float vysledek = mat.prvek[r][mat.n - 1] - suma;
            jePresny = jePresny && (fabs(vysledek - vystup.prvek[r][0]) < e);
            vystup.prvek[r][0] = vysledek;   
        }
    }

    return vystup;
}

TMatice jacobi(TMatice mat, float e)
{
    TMatice vystup;
    for (int i = 0; i < mat.m; i++) {
        vystup.prvek[i][0] = 0;
        vystup.prvek[i][1] = 0;
    }
    vystup.m = mat.m;
    vystup.n = 2;
    int novy = 0;
    bool jePresny = false;
    while (!jePresny) {
        jePresny = true;
        for (int r = 0; r < mat.m; r++)  {
            float suma = 0;
            for (int s = 0; s < mat.n - 1; s++) {
                suma += mat.prvek[r][s] * vystup.prvek[s][!novy];
            }
            vystup.prvek[r][novy] = mat.prvek[r][mat.n - 1] - suma;
            jePresny = jePresny && fabs(vystup.prvek[r][novy] - vystup.prvek[r][!novy]) < e;
        }
        novy = !novy;
    }

    return vystup;   
}

void vypis(TMatice m) 
{
    for (int r = 0; r < m.m; r++) {
        for (int s = 0; s < m.n; s++) {
            printf("%f ", m.prvek[r][s]);
        }
        puts("");
    }

}

int main(void) 
{
    FILE* f = fopen("13_matice.txt", "r");
    if (f == NULL) {
        return 1;
    }

    TMatice m;
    nacti(f, &m);

    optimalizace(&m);
    vypis(m);
    vypis(jacobi(m, 0.00001));

    fclose(f);
}
