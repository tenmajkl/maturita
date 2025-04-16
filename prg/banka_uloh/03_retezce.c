
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int pocetCislic(char retezec[], int* prvni, int* posledni)
{
    int cislice = 0;
    *prvni = -1;
    for (int i = 0; retezec[i] != '\0'; i++) {
        if (retezec[i] >= '0' && retezec[i] <= '9') {
            if (*prvni == -1) {
                *prvni = i;
            }
            cislice++;
            *posledni = i;
        }
    }
    
    return cislice;
}

void nahrad(char retezec[], char x, char y)
{
    for (int i = 0; retezec[i] != '\0'; i++) {
        if (retezec[i] == x) {
            retezec[i] = y;
        }
    }
}

void skryjCisla(char retezec[])
{
    for (int i = 0; retezec[i] != '\0'; i++) {
        if (retezec[i] >= '0' && retezec[i] <= '9') {
            retezec[i] = '#';
        }
    }
}

int pocetSlov(char retezec[])
{
    char stav = 'S';
    int slova = 0;
    for (int i = 0; true; i++) {
        switch (stav) {
            case 'S':
                if (isspace(retezec[i])) {
                    break;
                }

                if (retezec[i] == '\0') {
                    return slova;
                }

                stav = 'L';
                break;
            case 'L':
                if (isspace(retezec[i])) {
                    stav = 'S';
                    slova++;
                    break;
                }

                if (retezec[i] == '\0') {
                    slova++;
                    return slova;
                }
                break;
        }
    }

    return slova; // pro jistotu
}

void nahradMalaZaVelka(char retezec[])
{
    int posun = 'A' - 'a';
    for (int i = 0; retezec[i] != '\0'; i++) {
        if (retezec[i] >= 'a' && retezec[i] <= 'z') {
            retezec[i] += posun;
        }
    }
}

void nahradVelkaZaMala(char retezec[])
{
    int posun = 'A' - 'a';
    for (int i = 0; retezec[i] != '\0'; i++) {
        if (retezec[i] >= 'A' && retezec[i] <= 'Z') {
            retezec[i] -= posun;
        }
    }
}

void reverze(char retezec[])
{
    int delka = strlen(retezec);
    char h;
    for (int i = 0; i < delka/2; i++) {
        h = retezec[i];
        retezec[i] = retezec[delka - i - 1];
        retezec[delka - i - 1] = h;
    }
}

void reverzeRekurzivne(char retezec[], int delka)
{
    if (delka < 2) {
        return;
    }

    char h = retezec[0];
    retezec[0] = retezec[delka - 1];
    retezec[delka - 1] = h;

    reverzeRekurzivne(retezec + 1, delka - 2);
}

int main(void)
{
    char retezec[256];
    if (scanf("%255[^\n]", retezec) != 1) {
        return 1;
    }

    int prvni;
    int posledni;
    int cislice = pocetCislic(retezec, &prvni, &posledni);
    printf("pocet cislic: %i, prvni: %i, posledni: %i\n", cislice, prvni, posledni);

    char x = 'a';
    char y = 'b';

    nahrad(retezec, x, y);
    printf("nahrada znaku %c za %c: %s\n", x, y, retezec);

    skryjCisla(retezec);
    printf("skryta cislice: %s\n", retezec);

    nahradMalaZaVelka(retezec);
    printf("nahrazena mala a velka: %s\n", retezec);

    printf("pocet slov: %i\n", pocetSlov(retezec));

    reverzeRekurzivne(retezec, strlen(retezec));

    printf("otoceni: %s\n", retezec);

}
