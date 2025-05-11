#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char jmeno[11];
} TUzivatel;

typedef struct {
    int uzivatel_id;
    char email[21];
} TEmail;


void emailyUzivatele(FILE* uzivatele, FILE* emaily, char jmeno[]) 
{
    TUzivatel uzivatel;
    bool nalezeno = false;
    while (fscanf(uzivatele, "%i %10s", &uzivatel.id, uzivatel.jmeno)) {
        if (strcmp(uzivatel.jmeno, jmeno) == 0) {
            nalezeno = true;
            break;
        }
    }
    
    if (!nalezeno) {
        return;
    }

    TEmail email;
    while (fscanf(emaily, "%i %20s", &email.uzivatel_id, email.email)) {
        if (email.uzivatel_id == uzivatel.id) {
            printf("%s\n", email.email);
        }
    }

}
