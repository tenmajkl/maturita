#include <stdio.h>
#include <stdbool.h>

typedef unsigned int uint;
typedef unsigned char uchar;

void nadsit(uchar adresa[], uchar maska[], uchar vysledek[])
{
    uint* v = (uint*) vysledek;
    *v = *((uint*) adresa) & *((uint*) maska); 
}

void podsit(uchar adresa[], uchar maska[], uchar vysledek[])
{    
    uint* v = (uint*) vysledek;
    *v = *((uint*) adresa) & ~*((uint*) maska); 
}


void vypisAdresu(uchar adresa[])
{
    printf("%i.%i.%i.%i\n", adresa[0], adresa[1], adresa[2], adresa[3]);
}

// cenu za nejhorsi parsovani ziskava
bool jeMac(char* adresa)
{
    int _;
    return sscanf(adresa, "%2x:%2x:%2x:%2x:%2x:%2x", &_, &_, &_, &_, &_, &_) == 6;
}

bool jeIPV4(char* adresa)
{
    unsigned int a, b, c, d;
    if (sscanf(adresa, "%i.%i.%i.%i", &a, &b, &c, &d) != 4) {
        return false;
    }

    return a <= 255 && b <= 255 && c <= 255 && d <= 255;

}

// ????
bool jeIPV6(char* adresa)
{
    int _;
    return sscanf(adresa, "%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x", &_, &_, &_, &_, &_, &_, &_, &_) == 6;
}

bool jeEmail(char* vstup)
{
    // todo mat lepsi
    char jmeno[64];
    char domena[64];
    if (sscanf(vstup, "%63[^@]@%63s", jmeno, domena) != 2) {
        return false;
    }

    for (int i = 0; domena[i] != '\0'; i++) {
        if (domena[i] == '.') {
            if (domena[i + 1] != '\0' && domena[i + 2] != '\0') {
                return true;
            }
            return false;
        }
    }

    return false;
}

int main(void)
{
    uchar ip[4] = {192, 124, 36, 10};

    uchar maska[4] = {255, 255, 240, 0};

    uchar vysledek[4];

    nadsit(ip, maska, vysledek);

    vypisAdresu(vysledek);

    podsit(ip, maska, vysledek);

    vypisAdresu(vysledek);

    printf("%c", jeIPV4("192.124.36.1")? 'j' : 'n');

    return 1;
}
