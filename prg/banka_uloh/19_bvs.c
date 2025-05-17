#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _uzel {
    int klic;
    int hodnota;
    struct _uzel* levy;
    struct _uzel* pravy;
} TUzel;

typedef struct {
    TUzel* koren;
} TStrom;

TStrom* novyStrom() 
{
    TStrom* strom = malloc(sizeof(TStrom));
    if (strom == NULL) {
        return NULL;
    }

    strom->koren = NULL;
    return strom;
}

bool _pridej(TUzel** uzel, int klic, int hodnota)
{
    if (*uzel == NULL) {
        TUzel* novy = malloc(sizeof(TUzel));
        if (novy == NULL) {
            return false;
        }
        novy->klic = klic;
        novy->hodnota = hodnota;
        *uzel = novy;
        return true;
    }

    if (klic < (*uzel)->klic) {
        return _pridej(&(*uzel)->levy, klic, hodnota);
    }

    return _pridej(&(*uzel)->pravy, klic, hodnota);
}

bool pridejUzel(TStrom* strom, int klic, int hodnota) 
{
    return _pridej(&strom->koren, klic, hodnota);
}

bool nejpravejsi(TStrom* strom, int* hodnota)
{
    if (strom->koren == NULL) {
        return false;
    }

    TUzel* uzel = strom->koren;
    while (uzel->pravy != NULL) {
        uzel = uzel->pravy; 
    }

    *hodnota = uzel->hodnota;

    return true; 
}

bool nejlevejsi(TStrom* strom, int* hodnota)
{
    if (strom->koren == NULL) {
        return false;
    }

    TUzel* uzel = strom->koren;
    while (uzel->levy != NULL) {
        uzel = uzel->levy; 
    }

    *hodnota = uzel->hodnota;

    return true; 
}

// sestupne analogicky, ale rekurze bude prohozena
void _vzestupne(TUzel* uzel) 
{
    if (uzel == NULL) {
        return;
    }

    _vzestupne(uzel->levy);
    printf("%i\n", uzel->klic);
    _vzestupne(uzel->pravy);
}

void vzestupne(TStrom* strom)
{
    _vzestupne(strom->koren);
}

bool _najdi(TUzel* uzel, int klic, int* hodnota)
{
    if (uzel == NULL) {
        return false;
    }

    if (uzel->klic == klic) {
        *hodnota = uzel->hodnota;
        return true;
    }

    if (klic < uzel->klic) {
        return _najdi(uzel->levy, klic, hodnota);
    }

    return _najdi(uzel->pravy, klic, hodnota);
}

bool najdi(TStrom* strom, int klic, int* hodnota) 
{
    return _najdi(strom->koren, klic, hodnota);
}

bool _mensiKlice(TUzel* uzel, int klic)
{
    if (uzel == NULL) {
        return false;
    }

    if (uzel->klic == klic) {
        _vzestupne(uzel->levy);
        return true;
    }
    if (klic < uzel->klic) {
        return _mensiKlice(uzel->levy, klic);
    }

    _vzestupne(uzel->levy);
    printf("%i\n", uzel->klic);
    return _mensiKlice(uzel->pravy, klic);
}

bool mensiKlice(TStrom* strom, int klic)
{
    return _mensiKlice(strom->koren, klic);
}

void _zrus(TUzel* uzel)
{
    if (uzel == NULL) {
        return;
    }

    _zrus(uzel->levy);
    _zrus(uzel->pravy);
    free(uzel);
}

void zrusStrom(TStrom* strom)
{
    _zrus(strom->koren);
}

void _zrusList(TUzel** uzel, int klic)
{
    if (uzel == NULL) {
        return;
    }

    if ((*uzel)->klic == klic) {
        if ((*uzel)->levy == NULL && (*uzel)->pravy == NULL) {
            free(*uzel);
            *uzel = NULL;
        }
        return;
    }

    if (klic < (*uzel)->klic) {
        return _zrusList(&(*uzel)->levy, klic);
    }

    _zrusList(&(*uzel)->pravy, klic);
}

void zrusList(TStrom* strom, int klic)
{
    _zrusList(&strom->koren, klic);
}

int _vaha(TUzel* uzel)
{
    if (uzel == NULL) {
        return 0;
    }

    return _vaha(uzel->levy) + _vaha(uzel->pravy) + 1;
}

int vaha(TStrom* strom)
{
    return _vaha(strom->koren);
}

int _vyska(TUzel* uzel)
{
    if (uzel == NULL) {
        return 0;
    }

    int levy = _vyska(uzel->levy);
    int pravy = _vyska(uzel->pravy);

    int vetsi = levy > pravy ? levy : pravy;

    return vetsi + 1;
}

int vyska(TStrom* strom)
{
    return _vyska(strom->koren);
}

int main(void)
{
    TStrom* strom = novyStrom();
    pridejUzel(strom, 5, -5);
    pridejUzel(strom, 7, -7);
    pridejUzel(strom, 6, -6);
    pridejUzel(strom, 2, -2);
    pridejUzel(strom, 3, -3);
    pridejUzel(strom, 1, -1);
    vzestupne(strom);   
    int n;
    nejlevejsi(strom, &n);
    printf("%i\n", n);

    najdi(strom, 6, &n);
    printf("%i\n", n);

    mensiKlice(strom, 7);

    printf("vaha: %i\n", vaha(strom));
    printf("vyska: %i\n", vyska(strom));

    zrusList(strom, 6);
    vzestupne(strom);
    zrusList(strom, 5);
    vzestupne(strom);

    zrusStrom(strom);
}
