#include<stdio.h>
#include<string.h>
#include<math.h>

void odstranPicoviny(char* adresa)
{
    //int j = 0;
    //for (int i = 0; adresa[i] != '\0'; i++) {
    //    if (adresa[i] != '1' && adresa[i] != '0') {
    //        adresa[i] = adresa[++j];
    //        i--;
    //        continue;
    //    }
    //    adresa[i] = adresa[j];
    //    if (adresa[i] != '1' && adresa[i] != '0') {
    //        i--;
    //    }
    //    j++;
    //}
//    char pomocne[strlen(adresa)];
//    int j = 0;
//    for (int i = 0; adresa[i] != 0; i++) {
//        if (adresa[i] == '1' || adresa[i] == '0') {
//            pomocne[j++] = adresa[i];
//            continue;
//        }
//    }
//    pomocne[j] = 0;
//    strcpy(adresa, pomocne);

    // jak nahore ale nic nekopiruju a proce to delam v jednom poli -- prepisuju to co jsem uz precetl takze nedelam bordel
    // nevim co varim tpc
    int i = 0;
    int j = 0;
    while (adresa[i] != '\0') {
        if (adresa[i] == '0' || adresa[i] == '1') {
            adresa[j++] = adresa[i];
        }
        i++;
    }
    adresa[j] = '\0';
}

int mapujCifru(char cifra) 
{
    if (cifra <= '9' && cifra >= '0') {
        return cifra - '0';
    }

    if (cifra <= 'F' && cifra >= 'A') {
        return cifra - 'A' + 10;
    }

    return -1;
}

int architektura(char* adresa)
{
    long long int hodnota = 0; //!!!
    int cifra;
    for (int i = 0; adresa[i] != '\0'; i++) {
        cifra = mapujCifru(adresa[i]);
        if (cifra == -1) {
            return -1;
        }
        hodnota = hodnota * 16 + cifra;
    }
    
    // 8, 16, 32, 64
    double log = log2(hodnota);
    
    for (int i = 8; i <= 64; i *= 2) {
        if (log < i) {
            return i;
        }
    }

    return -1;

}

int main(void) 
{
    char s[64] = "p0p1119981010707189-7";
    odstranPicoviny(s);
    puts(s);

    printf("%i\n", architektura("FFFFFFFFF"));
}
