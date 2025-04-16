// ale hovno tady jdeme znovu

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nazev[21];
    int vyska;
    bool aktivni;
} TSopka;

typedef struct {
    TSopka* sopky;
    int pocet;
} TSeznamSopek;

TSeznamSopek* nactiSopky(FILE* vstup)
{
    TSeznamSopek* sopky = malloc(sizeof(TSeznamSopek));
    if (sopky == NULL) {
        return sopky;
    }
    sopky->pocet = 16;
    sopky->sopky = malloc(sopky->pocet * sizeof(TSopka));
    if (sopky->sopky == NULL) {
        free(sopky);
        return NULL;
    }

    int i = 0;
    int aktivni;
    while (fscanf(vstup, "%20[^,],%i,%i\n", sopky->sopky[i].nazev, &sopky->sopky[i].vyska, &aktivni) == 3) {
        sopky->sopky[i].aktivni = aktivni ? true : false;
        if (i == sopky->pocet - 1) {
            TSopka* nove = realloc(sopky->sopky, sizeof(TSopka) * sopky->pocet * 2);
            if (nove == NULL) {
                return sopky;
            }
            sopky->sopky = nove;
            sopky->pocet = sopky->pocet * 2;
        }
        i++;
    }

    sopky->pocet = i;

    TSopka* nove = realloc(sopky->sopky, i * sizeof(TSopka));
    if (nove == NULL) {
        return sopky; 
    }

    sopky->sopky = nove;
    
    return sopky;
}

int prumernaVyska(TSeznamSopek* sopky, bool aktivni)
{
    int soucet = 0;
    int pocet = 0;
    for (int i = 0; i < sopky->pocet; i++) {
        TSopka sopka = sopky->sopky[i];
        if (sopka.aktivni != aktivni) {
            continue;
        }

        soucet += sopka.vyska;
        pocet++;
    }

    return pocet == 0 ? 0 : soucet / pocet;
}

void vyssiNez(TSeznamSopek* sopky, int vyska, FILE* vystup)
{
    for (int i = 0; i < sopky->pocet; i ++) {
        TSopka sopka = sopky->sopky[i];
        if (sopka.vyska > vyska) {
            fprintf(vystup, "%s -- %s\n", sopka.nazev, sopka.aktivni ? "aktivni" : "neaktivni");  
        }
    }
}

void vypis(TSeznamSopek* sopky, bool aktivni, FILE* vystup)
{
    for (int i = 0; i < sopky->pocet; i++) {
        TSopka sopka = sopky->sopky[i];
        if (sopka.aktivni != aktivni) {
            continue;
        }
        fprintf(vystup, "%s,%i,%i\n", sopka.nazev, sopka.vyska, sopka.aktivni ? 1 : 0); 
    }
}


void uvolniSopky(TSeznamSopek* sopky)
{
    free(sopky->sopky);
    free(sopky);
}

int main(void)
{
    printf("zadej jmeno souboru: ");
    char jmeno[64];
    if (scanf("%63s", jmeno) != 1) {
        return 1; 
    }

    FILE* soubor = fopen(jmeno, "r");
    if (soubor == NULL) {
        return 1;
    }

    TSeznamSopek* sopky = nactiSopky(soubor);
    fclose(soubor);
    if (sopky == NULL) {
        return 1;
    }

    printf("prumerna vyska aktivnich sopek: %i\n", prumernaVyska(sopky, true));
    printf("prumerna vyska neaktivnich sopek: %i\n", prumernaVyska(sopky, false));

    puts("sopky vyssi nez 37");
    vyssiNez(sopky, 37, stdout);

    puts("aktivni sopky:");
    vypis(sopky, true, stdout);

    puts("neaktivni sopky:");
    vypis(sopky, true, stdout);

    uvolniSopky(sopky);
}
