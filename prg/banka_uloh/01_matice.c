#include <stdio.h>
#include<stdbool.h>

typedef struct {
    int prvek[32][32];
    int m;
    int n;
} TMatice;

bool nacti(FILE* vstup, TMatice* m) 
{
    if (fscanf(vstup, "%d %d", &m->m, &m->n) != 2) {
        return false;
    }

    for (int r = 0; r < m->m; r++) {
        for (int s = 0; s < m->n; s++) {
            if (fscanf(vstup, "%d", &m->prvek[r][s]) != 1) {
                return false;
            }
        }
    }
    
    return true;
}

void vypis(FILE* vystup, TMatice m)
{
    for (int r = 0; r < m.m; r++) {
        for (int s = 0; s < m.n; s++) {
            fprintf(vystup, "%d ", m.prvek[r][s]);
        }
        fprintf(vystup, "\n");
    }
}

void suda(TMatice* m) 
{
    for (int s = 0; s < m->n; s++) {
        int suda = 0;
        for (int r = 0; r < m->m; r++) {
            suda += !(m->prvek[r][s] % 2);
        }
        m->prvek[m->m - 1][s] = suda;
    }
}

int soucetObvodu(TMatice m)
{
    int soucet = 0;
    for (int s = 0; s < m.n; s++) {
        soucet += m.prvek[0][s] + m.prvek[m.m - 1][s];
    }

    for (int r = 1; r < m.m - 1; r++) {
        soucet += m.prvek[r][0] + m.prvek[r][m.n - 1];
    }

    return soucet;
}

int soucetUvnitr(TMatice m) 
{
    int soucet = 0;
    for (int r = 1; r < m.m - 1; r++) {
        for (int s = 1; s < m.n - 1; s++) {
            soucet += m.prvek[r][s];
        }
    }

    return soucet;
}

// TODO ask 
int soucetKvadrantu(TMatice m, int kvadrant)
{
    kvadrant--;
    static int mapa[4] = {1, 3, 2, 0};
    int soucet = 0;
    for (int r = 0; r < m.m / 2; r++) {
        for (int s = 0; s < m.n / 2; s++) {
            soucet += 
                m.prvek
                [(mapa[kvadrant] >> 1) * (m.m / 2) + r]
                [(mapa[kvadrant] & 1) * (m.n / 2) + s]
            ;
        }
    }

    return soucet;
}

int soucetCvrtin(TMatice m, int x, int y)
{
    int soucet = 0;
    for (int r = 0; r < m.m / 2; r++) {
        for (int s = 0; s < m.n / 2; s++) {
            soucet += 
                m.prvek
                [y * (m.m / 2) + r]
                [x * (m.n / 2) + s]
            ;
        }
    }

    return soucet;
}

bool jeVertikalneSymetricka(TMatice m) {
    for (int s = 0; s < m.n / 2; s++) {
        for (int r = 0; r < m.m; r++) {
            if (m.prvek[r][s] != m.prvek[r][m.n - s - 1]) {
                return false;
            }
        }
    }
    return true;
}

bool jeHorizontalneSymetricka(TMatice m) {
    for (int r = 0; r < m.m / 2; r++) {
        for (int s = 0; s < m.n; s++) {
            if (m.prvek[r][s] != m.prvek[m.m - r - 1][s]) {
                return false;
            }
        }
    }
    return true;
}

TMatice otoc(TMatice m, int n)
{
    TMatice nova;
    if (n % 2 == 0) {
        nova.m = m.m;
        nova.n = m.n;
    } else {
        nova.m = m.n; 
        nova.n = m.m;
    }

    for (int r = 0; r < m.m; r++) {
        for (int s = 0; s < m.n; s++) {
            int nove_r, nove_s;
            switch (n % 4) {
                case 0:
                    nove_r = r;
                    nove_s = s;
                    break;
                case 1:
                    nove_r = m.n - s - 1;
                    nove_s = r;
                    break;
                case 2:
                    nove_r = m.m - r - 1;
                    nove_s = m.n - s - 1;
                    break;
                case 3:
                    nove_r = s;
                    nove_s = r;
                    break;
            }
            nova.prvek[nove_r][nove_s] = m.prvek[r][s];
        }
    }

    return nova;
}


int main(void) 
{
    FILE* f = fopen("01_matice.txt", "r");
    if (f == NULL) {
        printf("spatny soubor");
        return 1;
    }

    TMatice m;
    nacti(f, &m);
    vypis(stdout, m);
    printf("soucet obdovu: %i \n", soucetObvodu(m));
    printf("soucet uvnitr: %i \n", soucetUvnitr(m));
    for (int i = 1; i <= 4; i++) {
        printf("soucet v %i. kvadrantu: %i\n", i, soucetKvadrantu(m, i));
    }

    printf("%i\n", soucetCvrtin(m, 0, 1));
    TMatice vert = {
        {
            {1, 2, 1},
            {3, 4, 3}
        },
        2, 3
    };
    printf("%i\n", jeVertikalneSymetricka(vert));
    TMatice hor = {
        {
            {1, 2, 9},
            {1, 6, 9},
            {1, 2, 9}
        },
        3, 3
    };
    printf("%i\n", jeHorizontalneSymetricka(hor));

    vypis(stdout, otoc(m, 3));

    suda(&m);
    vypis(stdout, m);

    fclose(f);
}
