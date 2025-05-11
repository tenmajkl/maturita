#include <stdio.h>

typedef struct {
    float* koeficienty;
    int stupen;
} TPolynom;

float horner(TPolynom p, float x) 
{
    float vysledek = 0;
    for (int i = 0; i <= p.stupen; i++) {
        vysledek = vysledek * x + p.koeficienty[i];
    }

    return vysledek;
}

float bisekce(TPolynom p, float a, float b, float e)
{
    float c = (a + b) / 2;
    float fc;
    float fa = horner(p, a);
    while ((fc = horner(p, c)) >= e) {
        if (fa * c < 0) {
            b = c;
        } else {
            a = c;
            fa = fc;
        }
        c = (a + b) / 2;
    }

    return c;
}

float regulaFalsi(TPolynom p, float a, float b, float e)
{
    float fc;
    float fa = horner(p, a);
    float fb = horner(p, b);
    float c = (b * fa - a * fb) / (fa - fb);
    while ((fc = horner(p, c)) >= e) {
        if (fa * c < 0) {
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }
        c = (b * fa - a * fb) / (fa - fb);
    }

    return c;
}

float secen(TPolynom p, float a, float b, float e)
{
    float fa = horner(p, a);
    float fb = horner(p, b);
    float c = (b * fa - a * fb) / (fa - fb);
    float fc;
    while ((fc = horner(p, c)) >= e) {
        fa = fb;
        fb = fc;
        a = b;
        b = c;
        c = (b * fa - a * fb) / (fa - fb);
    }

    return c;
}

float newton(TPolynom p, TPolynom dp, float x, float e)
{
    float fx, dfx;
    while ((fx = horner(p, x)) >= e) {
        dfx = horner(dp, x);
        if (dfx == 0) {
            return 0.0/0.0;
        }
        x = x - (fx / dfx);
    }
    return x;
}

int main(void)
{
    float exponents[7] = {12, 0.7, 3, 0, 6, 22, 4.62};
    TPolynom p = {
        exponents,
        6,
    };

    float de[6] = {72, 3.5, 12, 0, 12, 22};
    TPolynom dp = {
        de, 
        5,
    };

    printf("%f\n", horner(p, 7.1));
    printf("%f\n", bisekce(p, -1, -0.9, 0.0000001));
    printf("%f\n", regulaFalsi(p, -1, -0.9, 0.0000001));
    printf("%f\n", secen(p, -1, -0.9, 0.0000001));
    printf("%f\n", newton(p, dp, -1, 0.0000001));
}
