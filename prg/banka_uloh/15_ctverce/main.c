#include "matice.h"
#include "pole.h"
#include "matice.h"
#include<stdio.h>

double konstantniRegrese(double y[], int n) 
{
    if (n == 0) {
        return 0.0/0.0;
    }

    double soucet = 0;
    for (int i = 0; i < n; i++) {
        soucet += y[i];
    }

    return soucet / n;
}

void linearniRegrese(double x[], double y[], int n, double* a, double* b)
{
    double x2s = 0;
    double xs = 0;
    double yxs = 0;
    double ys;

    for (int i = 0; i < n; i++) {
        x2s += x[i] * x[i];
        xs += x[i];
        yxs += x[i] * y[i];
        ys += y[i];
    }
    Tmatice* mat = novaMatice(2, 3);
    mat->prvek[0][0] = x2s;
    mat->prvek[0][1] = xs;
    mat->prvek[0][2] = yxs;
    mat->prvek[1][0] = xs;
    mat->prvek[1][1] = (double) n;
    mat->prvek[1][2] = ys;

    vyresSoustavu(mat);
    *a = mat->prvek[0][2];
    *b = mat->prvek[1][2];
}
int main(void)
{
    double a;
    double b;
//    printf("%f", konstantniRegrese(TAB_Y, TAB_LEN));
    linearniRegrese(TAB_X, TAB_Y, TAB_LEN, &a, &b);
    printf("%f %f", a, b);
}
