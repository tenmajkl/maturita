#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _tuzel {
    char hodnota;
    struct _tuzel* dalsi;
} TUzel;

typedef struct {
    TUzel* vrchol;
} TZasobnik;

typedef struct {
    TUzel* zacatek;
    TUzel* konec;
} TFronta;

TFronta* novaFronta()
{
    TFronta* z = malloc(sizeof(TFronta));
    if (z == NULL) {
        return NULL;
    }
    z->zacatek = NULL;
    z->konec = NULL;

    return z;
}

bool enque(TFronta* fronta, char hodnota)
{
    TUzel* u = malloc(sizeof(TUzel));
    if (u == NULL) {
        return false;
    }

    u->hodnota = hodnota;

    // DONT FORGOR
    if (fronta->zacatek == NULL) {
        fronta->zacatek = u;
    } else {
        fronta->konec->dalsi = u;
    }
    fronta->konec = u;
    return true;
}


bool deque(TFronta* fronta, char* hodnota)
{
    if (fronta->zacatek == NULL) {
        return false;
    }
    TUzel* u = fronta->zacatek;
    fronta->zacatek = u->dalsi;
    *hodnota = u->hodnota;
    if (fronta->konec == u) {
        fronta->konec = NULL;
    }
    free(u);

    return true;
}

void uvolniFrontu(TFronta* fronta)
{
    char _;
    while (deque(fronta, &_)) { }
    free(fronta);
}

TZasobnik* novyZasobnik()
{
    TZasobnik* z = malloc(sizeof(TZasobnik));
    if (z == NULL) {
        return NULL;
    }
    z->vrchol = NULL;

    return z;
}

bool push(TZasobnik* z, char hodnota)
{
    TUzel* u = malloc(sizeof(TUzel));
    if (u == NULL) {
        return false;
    }

    u->hodnota = hodnota;
    u->dalsi = z->vrchol;
    z->vrchol = u;

    return true;
}

bool pop(TZasobnik* z, char* hodnota)
{
    if (z->vrchol == NULL) {
        return false;
    }

    *hodnota = z->vrchol->hodnota;
    TUzel* vrchol = z->vrchol;
    z->vrchol = vrchol->dalsi;
    free(vrchol);
    return true;
}

bool top(TZasobnik* z, char* hodnota)
{
    if (z->vrchol == NULL) {
        return false;
    }

    *hodnota = z->vrchol->hodnota;
    return true;
}


void uvolniZasobnik(TZasobnik* z)
{
    char _;
    while (pop(z, &_)) { }
    free(z);
}

char uzaviraci(char zavorka)
{
    switch (zavorka) {
        case '[': return ']'; break;
        case '{': return '}'; break;
        case '<': return '>'; break;
        case '(': return ')'; break;
        default: return zavorka;
    }
}

bool jeZaviraci(char zavorka)
{
    return 
        zavorka == ']'
        || zavorka == '}'
        || zavorka == '>'
        || zavorka == ')'
    ;
}

bool zavorky(FILE* vstup)
{
    TZasobnik* z = novyZasobnik();
    if (z == NULL) {
        return false;
    }

    char c;
    char konec;
    while ((c = fgetc(vstup)) != EOF) {
        if (jeZaviraci(c)) {
            char zkonec;
            if (!pop(z, &zkonec)) {
                uvolniZasobnik(z);
                return false;
            }
            if (zkonec != c) {
                uvolniZasobnik(z);
                return false;
            }
        }
        konec = uzaviraci(c);
        if (konec != c) {
            push(z, konec);
        }
    }

    bool vysledek = z->vrchol == NULL;
    uvolniZasobnik(z);

    return vysledek;
}

void posledichN(FILE* vstup, FILE* vystup, int n)
{
    TFronta* f = novaFronta();
    if (f == NULL) {
        return;
    }

    char c;
    // 0 protoze zacinam odebirat az u 5 prvku
    int i = 0;
    while ((c = fgetc(vstup)) != EOF) {
        enque(f, c);
        if (i == n) {
            deque(f, &c);
        } else {
            i++;
        }
    }

    while (deque(f, &c)) {
        fputc(c, vystup);
    }

    uvolniFrontu(f);
}


int main(void)
{
//    printf("zavorky: %c\n", zavorky(stdin) ? 'a' : 'n');
    posledichN(stdin, stdout, 4);
}
