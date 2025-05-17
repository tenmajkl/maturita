#include <stdbool.h>
#include <stdio.h>

int hledani(int pole[], int n, int klic)
{
    for (int i = 0; i < n; i++) {
        if (pole[i] == klic) {
            return i;
        }
    }

    return -1;
}

int hledaniSeZarazkou(int pole[], int n, int klic)
{
    pole[n] = klic;
    int i = 0;
    while (pole[i] != klic) {
        i++;
    }
    return i == n ? -1 : i;
}

bool jeSerazeno(int pole[], int n) 
{
    for (int i = 0; i < n - 1; i++) {
        if (pole[i] > pole[i + 1]) {
            return false;
        }
    }

    return true;
}

int serazeneHledani(int pole[], int n, int klic) 
{
    int i = 0;
    while (i < n && pole[i] < klic) {
        i++;
    }
    return pole[i] == klic ? i : -1;
}

int serazeneHledaniSeZarazkou(int pole[], int n, int klic) 
{
    pole[n] = klic;
    int i = 0;
    while (pole[i] < klic) {
        i++;
    }
    return (i != n && pole[i] == klic) ? i : -1;
}

int binarniVyhledavani(int pole[], int n, int klic)
{
    int start = 0;
    int cil = n;
    while (cil > start) {
        int stred = (start + cil) / 2;
        if (klic == pole[stred]) {
            return stred;
        }

        if (klic < pole[stred]) {
            cil = stred;
            continue;
        }

        start = stred + 1;
    }

    return -1;
}

int main(void)
{
    int n = 9;
    //int sexAPrdel[10] = {1, 69, 5, 4, 420, 28, 81, 93, 74};

    //printf("%i\n", hledaniSeZarazkou(sexAPrdel, n, 420));

    int prdelASex[10] = {1, 2, 3, 4, 5, 7, 8, 9, 10};
    
    printf("%i\n", binarniVyhledavani(prdelASex, n, 10));

}
