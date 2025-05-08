#include <stdio.h>
#include <stdbool.h>

void prepis(FILE* vstup, FILE* vystup, char* retezec)
{
    char c;
    while ((c = fgetc(vstup)) != EOF) {
        if (c == '#') {
            fputs(retezec, vystup);
        } else {
            fputc(c, vystup);
        }
    }
}

bool zkopirujRadek(FILE* vstup, FILE* vystup)
{
    char c;
    while ((c = fgetc(vstup)) != '\n') {
        if (c == EOF) {
            return false;
        }
        fputc(c, vystup);
    }
    fputc('\n', vystup);

    return true;
}

void naPreskacku(FILE* a, FILE* b, FILE* vystup)
{
    bool neniKonec = true;
    while(neniKonec) {
        neniKonec = zkopirujRadek(a, vystup);
        neniKonec = zkopirujRadek(b, vystup) || neniKonec; 
    }
}

void pocetSlov(FILE* vstup, FILE* vystup)
{
    char c;
    int pocet = 0;
    bool mezery = false;
    bool novyRadek = false;
    while ((c = fgetc(vstup)) != EOF) {
        switch (c) {
            case ' ':
                if (mezery) {
                    break;
                }
                mezery = true;
                pocet++;
                break;
            case '\n':
                if (!novyRadek && !mezery) {
                    pocet++;
                }
                fprintf(vystup, "%i\n", pocet);
                pocet = 0;
                novyRadek = true;
                break;
            default:
                mezery = false;
                novyRadek = false;
        }
    }
}

void pocetSlovMat(FILE* vstup, FILE* vystup)
{
    char c;
    int pocet = 0;
    char stav = 's';
    while ((c = fgetc(vstup)) != EOF) {
        switch (stav) {
            case 's':
                if (c == ' ') {
                    break;
                }
                if (c == '\n') {
                    fprintf(vystup, "0\n");
                    break;
                }
                stav = 'a';
                break;
            case 'a':
                if (c == '\n') {
                    stav = 's';
                    fprintf(vystup, "%i\n", pocet + 1);
                    pocet = 0;
                    break;
                }

                if (c == ' ') {
                    stav = 'b';
                    pocet++;
                    break;
                }
                break;
            case 'b':
                if (c == '\n') {
                    stav = 's';
                    fprintf(vystup, "%i\n", pocet);
                    pocet = 0;
                    break;
                }

                if (c != ' ') {
                    stav = 'a';
                }
                break;
        }
    }

    if (stav == 'a') {
        pocet++;
    }
    
    if (pocet != 0) {
        fprintf(vystup, "%i\n", pocet);
    }

}

bool najdiVSouboru(FILE* f, int n)
{
    if (n <= 0) {
        return false;
    }
    int x;
    while (fscanf(f, "%i", &x) == 1) {
        if (x == n) {
            return true;
        }
    }

    return false;
}

int main(void)
{
//    prepis(stdin, stdout, "kombajn");

//    FILE* a = fopen("01_matice.txt", "r");
//    if (a == NULL) {
//        return 1;
//    }
//    FILE* b = fopen("04_sopky.txt", "r");
//    if (b == NULL) {
//        fclose(a);
//        return 1;
//    }
//    naPreskacku(a, b, stdout);
//    fclose(a);
//    fclose(b);

//    pocetSlovMat(stdin, stdout);

    printf("%c\n", najdiVSouboru(stdin, 10) ? 'y' : 'n');
}
