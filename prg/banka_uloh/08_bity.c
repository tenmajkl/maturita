// and
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void soucin(char a[], char b[], char c[])
{
    for (int i = 0; i < 16; i++) {
        c[i] = (a[i] - '0' && b[i] - '0') + '0';
    }
}

// or
void soucet(char a[], char b[], char c[])
{
    for (int i = 0; i < 16; i++) {
        c[i] = (a[i] - '0' || b[i] - '0') + '0';
    }
}

int xor(int x, int y)
{
    return ((x || y) && !(x && y)); 
}

// xor 
void exkluzivniSoucet(char a[], char b[], char c[])
{
    for (int i = 0; i < 16; i++) {
        int x = a[i] - '0';
        int y = b[i] - '0';
        c[i] = xor(x, y) + '0';
    }
}

void bitovyPosun(char a[], int n, char c[])
{
    strcpy(c, "0000000000000000");
    for (int i = 0; i < 16; i++) {
        int nova = i + n;
        if (nova < 0 || nova > 15) {
            continue;
        }

        c[nova] = a[i];
    }
}

void bitovaRotace(char a[], int n, char c[])
{
    for (int i = 0; i < 16; i++) {
        int nova = i + n;
        nova = (nova < 0 ? 16 + nova : nova) % 16;

        c[nova] = a[i];
    }
}

// TODO
// behem zkousky si asi nakreslim scitacku a naprogramuju podle toho
void aritmetickySoucet(char a[], char b[], char c[])
{
    int zbytek = 0;
    for (int i = 15; i >= 0; i--) {
        int x = a[i] - '0';
        int y = b[i] - '0';
        int z = xor(x, y);
        int s = xor(z, zbytek);
        zbytek = (x && y) || (z && zbytek);
        c[i] = s + '0';
    }
}

int main(void)
{
    char c[17];
    c[16] = '\0';
    char a[17] = "1001011100011110";
    char b[17] = "0011100100100111";

    soucin(a, b, c);
    printf("%s\n", c);
    
    soucet(a, b, c);
    printf("%s\n", c);
    
    exkluzivniSoucet(a, b, c);
    printf("%s\n", c);

    bitovyPosun(a, 5, c);
    printf("%s\n", c);

    bitovyPosun(a, -5, c);
    printf("%s\n", c);

    bitovaRotace(a, 5, c);
    printf("%s\n", c);

    bitovaRotace(a, -5, c);
    printf("%s\n", c);

    aritmetickySoucet("0000000000000111", "0000000000000011", c);
    printf("%s", c);
}
