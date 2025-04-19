#include <stdio.h>
#include <stdbool.h>

bool jeVPoli(char pole[], int pocet, char znak)
{
    for (int i = 0; i < pocet; i++) {
        if (pole[i] == znak) {
            return true;
        }
    }

    return false;
}

int jeVeta(char sigma[], int pocetZnaku, FILE* vstup, char konec)
{
    char c;
    int i = 0;
    while ((c = fgetc(vstup)) != konec) {
        if (!jeVPoli(sigma, pocetZnaku, c)) {
            return i;
        }
        i++;
    }

    return -1;
}

bool zavorkyBasic(FILE* vstup)
{
    int p = 0;
    char c;
    while ((c = fgetc(vstup)) != EOF) {
        if (c == '[') {
            p++;
        }

        if (c == ']') {
            p--;
            if (p < 0) {
                return false;
            }
        }
    }

    return p == 0;
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

bool zavorkyFull(FILE* vstup, char konec)
{
    char c;
    char zavorka;
    while ((c = fgetc(vstup)) != konec) {
        if (c == EOF) {
            return false;
        }

        if (jeZaviraci(c)) {
            return false;
        }

        zavorka = uzaviraci(c);
        if (zavorka == c) {
            continue;
        }

        if (!zavorkyFull(vstup, zavorka)) {
            return false;
        }
        
    }

    return true;
}

int main(void)
{ 
    // spinavy hack abych to tady nemusel jak picus vypisovat znak po znaku
    //char sigma[10] = "eilortv 6";
    //sigma[9] = '9';

    //printf("%i\n", jeVeta(sigma, 10, stdin, '\n'));

    //printf("%i\n", zavorkyBasic(stdin) ? 1 : 0);

    printf("%i\n", zavorkyFull(stdin, EOF) ? 1 : 0);

}
