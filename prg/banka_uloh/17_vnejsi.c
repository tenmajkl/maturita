#include <stdio.h>

int nactiZnak(FILE* f)
{
    int c;
    while ((c = fgetc(f)) == '\n') {
        
    }
    return c;
}

void sluc(FILE* a, FILE* b, FILE* c)
{
    int ch_a = nactiZnak(a);
    int ch_b = nactiZnak(b);
    while (ch_a != EOF && ch_b != EOF) {
        if (ch_a <= ch_b) {
            fputc(ch_a, c);
            ch_a = nactiZnak(a);
            continue;
        }

        fputc(ch_b, c);
        ch_b = nactiZnak(b);
    }

    while (ch_a != EOF) {
        fputc(ch_a, c);
        ch_a = nactiZnak(a);
    }

    while (ch_b != EOF) {
        fputc(ch_b, c);
        ch_b = nactiZnak(b);
    }
}

void slucPoJednom(FILE* a, FILE* b, FILE* c)
{
    int ch_a, ch_b, h;
    while ((ch_a = nactiZnak(a)) != EOF && (ch_b = nactiZnak(b)) != EOF) {
        if (ch_a > ch_b) {
            h = ch_a;
            ch_a = ch_b;
            ch_b = h;
        }

        fputc(ch_a, c);
        fputc(ch_b, c);
    }

    while ((ch_a = nactiZnak(a)) != EOF) {
        fputc(ch_b, c);
    }

    while ((ch_b = nactiZnak(b)) != EOF) {
        fputc(ch_b, c);
    }
}

void rozdel(int n, FILE* a, FILE* b, FILE* c) 
{
    int i = 0;
    FILE* soubor = b;
    int chachar;
    while ((chachar = nactiZnak(a)) != EOF) {
        if (i == n) {
            soubor = soubor == b ? c : b; 
            i = 0;
        }
        fputc(chachar, soubor);
        i++;
    }
}

int main(void) 
{
    FILE* a = fopen("17_a.txt", "r");
    if (a == NULL) {
        return 69;
    }

    FILE* b = fopen("17_b.txt", "r");
    if (b == NULL) {
        fclose(a);
        return 69;
    }

    FILE* c = fopen("17_c.txt", "w");
    if (c == NULL) {
        fclose(a);
        fclose(b);
        return 69;
    }

    FILE* d = fopen("17_d.txt", "w");
    if (d == NULL) {
        fclose(a);
        fclose(b);
        fclose(c);
        return 69;
    }

    rozdel(3, a, c, d);

    fclose(a);
    fclose(b);
    fclose(c);
    fclose(d);
}
