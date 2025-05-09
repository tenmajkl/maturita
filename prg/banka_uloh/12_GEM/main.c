/* Téma matice a moduly - varianta s polem pevných rozměrů
 *
 * Autor: MIchal Kripac 
 * Datum: 2024-09-24
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <float.h>
#include <time.h>

#include "gvid.h"
#include "matice.h"


/** \brief Otestuje operace #novaMatice, #nahodnaMatice a #tiskniMatici.stdout,  */
void testInit(void)
{
  printf("==========================================\n");
  printf("Test vytvoreni a inicializace matice\n");
  Tmatice * matice = novaMatice(5, 3);
//  maticeNastavPrvky(matice, 1.2);
  nahodnaMatice(matice);
  tiskniMatici(stdout, matice);

  uvolniMatici(matice);

  printf("==========================================\n");
}





/** \brief Otestuje funkce pro čtení ze a zápis do souboru.
 *
 * \param input char*   Jméno vstupního souboru nebo NULL
 * \param output char*  Jméno výstupního souboru nebo NULL
 * \return int Vrací EXIT_FAILURE v případě chyby při práci se soubory.
 *
 * <p>Pokud je místo jména vstupního nebo výstupního souboru prázdný ukazatel
 * NULL, použije se soubor stdin nebo stdout.</p>
 *
 */
int testFileRW(char *input, char *output)
{
  printf("==========================================\n");
  printf("Test cteni a zapisu ze a do souboru\n");
  FILE *fin = stdin;
  FILE *fout = stdout;

  int exitCode = EXIT_SUCCESS;

  if (input != NULL)
    fin = fopen(input, "r");

  if (output != NULL)
    fout = fopen(output, "w");

  if (fin == NULL)
  {
    fprintf(stderr, "Chybny nazev vstupniho souboru.");
    fin = stdin;
    input = NULL;
  }

  if (fout == NULL)
  {
    fprintf(stderr, "Chybny nazev vystupniho souboru.");
    fout = stdout;
    output = NULL;
  }

  Tmatice * m = nactiMatici(fin); // připravím si prázdnou matici
  if (m != NULL)
  {
    tiskniMatici(fout, m);
    uvolniMatici(m);
  }
  else
  {
    fprintf(stderr, "Chyba pri cteni vstupniho souboru.");
    exitCode = EXIT_FAILURE;
  }


  if (input != NULL) fclose(fin);
  if (output != NULL) fclose(fout);
  printf("==========================================\n");
  return exitCode;
}


/** \brief Vynásobí dvě matice a výsledek uloží do třetí nové matice.
 *
 * \param a const Tmatice* První vstupní matice.
 * \param b const Tmatice* Druhá vstupní matice.
 * \param c Tmatice* Výsledná, zatím nevytvořená matice.
 * \return bool Vrací true, pokud se operace povedla, jinak false.
 *
 * <p>Parametr c musí ukazovat na prozatím nevytvořenou matici, jinak dojde ke
 * ztrátě dat.</p>
 *
 * <p>Pokud jsou vstupní matice kompatibilní, tj. a->sloupcu == b->radku, dojde
 * k vytvoření výsledné matice o rozměrech c->radku = a-radku a c->sloupcu = b->sloupcu.
 * Do této matice pak bude uložen výsledek násobení a*b v tomto pořadí.</p>
 *
 * <p>Pozor! Operace maticového násobení není komutativní, tudíž záleží na
 * pořadí operandů.</p>
 */
Tmatice * maticeMult(const Tmatice *a, const Tmatice *b)
{
  if (a->sloupcu != b->radku)
    return NULL;

  Tmatice * c = novaMatice(a->radku, b->sloupcu);
  if (c == NULL)
    return NULL;

  for (int row = 0; row < c->radku ; ++row)
  {
    for (int col = 0; col < c->sloupcu ; ++col)
    {
      double ssum;
      ssum = 0.0;
      for (int k = 0; k < a->sloupcu ; ++k)
      {
        ssum += a->prvek[row][k] * b->prvek[k][col];
      }
      c->prvek[row][col] = ssum;
    }
  }
  return c;

//  Poznámka: Všimni si, že operace se sama stará o alokaci výsledku a ošetření
//  chyb, které to může generovat. Jako autor takové operace nemůžu chtít po
//  uživateli (této funkce), aby před samotným spuštěním funkce prováděl nějaké
//  kroky nutné pro správné chování této funkce. Programy, které toto vyžadují,
//  jsou takzvaně "křehké", což je protiklad k programům "robustním".
}

/** \brief Test operací #nahodnaMatice a #maticeMult. */
void testMult(void)
{
  printf("==========================================\n");
  printf("Test nasobeni nahodnych matic\n");
  Tmatice * a = novaMatice(4, 2);
  Tmatice * b = novaMatice(2, 3);

  nahodnaMatice(a);
  nahodnaMatice(b);

  tiskniMatici(stdout, a);
  printf("*\n");
  tiskniMatici(stdout, b);
  printf("=\n");
  Tmatice * c = maticeMult(a, b);
  if (c != NULL)
  {
    tiskniMatici(stdout, c);
    uvolniMatici(c);
  }
  else
    printf("Tohle nejde!\n");

  uvolniMatici(a);
  uvolniMatici(b);
  printf("==========================================\n");
}




/** \brief Vrátí index řádku s pivotem.
 *
 * Poznámka: Použij funkci fabs pro práci s absolutní hodnotou.
 *
 * \param m Tmatice* Ukazatel na rozšířenou matici soustavy.
 * \param r int Index referenčního řádku (a sloupce)
 * \return int Index řádku s pivotem.
 *
 */
int maxAbsPivot(Tmatice *m, int r)
{
    int max_i = r;
    double max_v = fabs(m->prvek[r][r]);
    for (int i = r + 1; i < m->radku; i++) {
        if (fabs(m->prvek[i][r]) > max_v) {
            max_i = i;
            max_v = fabs(m->prvek[i][r]);
        }
    }

    return max_i;
}

/** \brief Testuje, zda je zadaná soustava ve tvaru horní trojúhelníkové matice.
 *
 * \param m Tmatice* Ukazatel na rozšířenou matici soustavy.
 * \return bool Vrací logickou hodnotu.
 *
 */
bool jeHorni(Tmatice *m)
{
    for (int i = 1; i < m->radku; i++) {
        for (int j = 0; j < i; j++) {
            if (m->prvek[i][j] != 0) {
                return false;
            }
        }

        if (m->prvek[i][i] == 0) {
            return false;
        }
    }

    return true;
}

void kombinace(Tmatice* m, int r, int k, double c)
{
    for (int i = r; i < m->sloupcu; i++) {
        m->prvek[k][i] = m->prvek[r][i] * c - m->prvek[k][i];
    }
}

void radkoveUpravy(Tmatice* m, int r)
{
    for (int i = r + 1; i < m->radku; i++) {
        kombinace(m, r, i, m->prvek[i][r] / m->prvek[r][r]);
    }
}

/** \brief Provede přímý chod GEM.
 *
 * Změní vstupní matici na ekvivalentní horní trojúhelníkovou matici. Využije
 * přitom pivotování a ekvivalentních úprav.
 *
 * Poznámka: Vytvoř si samostatnou funkci pro pivotování a samostatnou funkci
 * pro aplikaci ekvivalentních úprav (nulování prvků pod diagonálním prvkem),
 * které zde zavoláš.
 *
 * \param m Tmatice* Ukazatel na rozšířenou matici soustavy.
 * \return int Vrací kód chyby.
 */
int gemPrimy(Tmatice *m)
{
    for (int r = 0; r < m->radku; r++) {
        int max = maxAbsPivot(m, r);
        if (m->prvek[max][r] == 0) {
            return 1; 
        }
        if (max != r) {
            prohodRadky(m, max, r);
        }

        radkoveUpravy(m, r);
    }

    return 0;
}

/** \brief Provede přímý chod GJEM.
 *
 * Změní vstupní matici na ekvivalentní diagonální matici.
 *
 * Poznámka: Výsledná matice může, ale nemusí být jednotková.
 *
 * Poznámka: Funkci vytvoříš úpravou funkce gemPrimy.
 *
 * \param m Tmatice* Ukazatel na rozšířenou matici soustavy.
 */
void gjemPrimy(Tmatice *m)
{
  printf("Funkce gjemPrimy neni hotova.");
}

/** \brief Test přímého chodu, tj. operací #gemPrimy a #gjemPrimy.
 *
 * Zadání:
 * Pro řešení využij funkce z modulu matice.h a funkce #gemPrimy a #gjemPrimy.
 * 1. Načti soubor s maticí (nebo si ji inicializuj přímo tady ve funkci).
 *    Pomocí funkce #maticeDuplikat si vyrob její duplikát.
 * 2. Proveď na ní přímý chod GEM a vytiskni výsledek.
 * 2. Na duplikátu vstupní matice proveď přímý chod GJEM a vytiskni výsledek.
 * 3. Ukliď po sobě.
 */
void testPrimehoChodu(char *jmenoSouboru)
{
  printf("==========================================\n");
  printf("Test pivotovani\n");

  FILE* f = fopen(jmenoSouboru, "r");
  if (f == NULL) {
    printf("nepovedlo se otevrit soubro");
    return;
  }

  Tmatice *matice = nactiMatici(f);
  if (matice == NULL) {
    printf("nepovedlo se nacist matici to me mrzi");
    return;
  }

  gemPrimy(matice);

  tiskniMatici(stdout, matice);

  printf("%c", jeHorni(matice) ? 'j' : 'n');

  fclose(f);
  uvolniMatici(matice);

  printf("==========================================\n");

}






/** \brief Vrací počet řešení upravené soustavy po provedení přímého chodu GEM.
 *
 * Součástí testu jsou i správné rozměry.
 *
 * \param m Tmatice* Ukazatel na rozšířenou matici soustavy.
 * \return bool Vrací hodnotu 1, když matice je rozšířenou maticí soustavy
 *              ve tvaru po provedení přímého chodu Gaussovy eliminační metody
 *              a soustava je dále řešitelná. Hodnotu 0 vrací, když soustava
 *              není ve tvaru horní trojúhelníkové matice nebo nemá žádné
 *              řešení. Hodnotu -1 vrací, když má soustava nekonečně mnoho
 *              řešení.
 */
int gemPoPrimem(Tmatice *m)
{
    if (!jeHorni(m)) {
        return 0;
    }

    double xn = m->prvek[m->radku - 1][m->sloupcu - 2];
    double bn = m->prvek[m->radku - 1][m->sloupcu - 1];
    if (xn == 0) {
        return bn == 0 ? -1 : 0;
    }

    return 1;

}

/** \brief Vrací počet řešení upravené soustavy po provedení přímého chodu GJEM.
 *
 * Součástí testu jsou i správné rozměry.
 *
 * \param m Tmatice* Ukazatel na rozšířenou matici soustavy.
 * \return bool Vrací hodnotu 1, když matice je rozšířenou maticí soustavy
 *              ve tvaru po provedení přímého chodu Gauss-Jordanovy eliminační
 *              metody a soustava je dále řešitelná. Hodnotu 0 vrací, když
 *              soustava není ve tvaru diagonální matice nebo nemá žádné
 *              řešení. Hodnotu -1 vrací, když má soustava nekonečně mnoho
 *              řešení.
 */
int gjemPoPrimem(Tmatice *m)
{
}

/** \brief Test matic po přímém chodu
 *
 * Zadání:
 * Pro řešení využij předchozí hotové funkce.
 * 1. Načti soubor s maticí (nebo si ji inicializuj přímo tady ve funkci).
 * 2. Otestuj ji a vytiskni, zda jde o matici po provedení přímého chodu GEM nebo GJEM.
 * 3. Pokud nejde o upravenou matici, proveď přímý chod GEM, GJEM (funkce pro
 *    to už máš hotové).
 * 4. Výsledek znovu otestuj.
 * 5. Vypiš, kolik řešení zadaná soustava má (0, 1, nekonečno).
 */
void testMaticePoPrimemChodu(char *jmenoSouboru)
{
  printf("==========================================\n");
  printf("Test pivotovani\n");

  FILE* f = fopen(jmenoSouboru, "r");
  if (f == NULL) {
    printf("nepovedlo se otevrit soubro");
    return;
  }

  Tmatice *matice = nactiMatici(f);
  if (matice == NULL) {
    printf("nepovedlo se nacist matici to me mrzi");
    return;
  }

  gemPrimy(matice);

  printf("pocet reseni: %i\n", gemPoPrimem(matice));

  fclose(f);
  uvolniMatici(matice);

  printf("==========================================\n");


}



/** \brief Provede zpětný chod GEM.
 *
 * Hodnoty neznámých nastaví do posledního sloupce rozšířené matice soustavy.
 *
 * \param m Tmatice* Ukazatel na rozšířenou matici soustavy.
 */
void gemZpetny(Tmatice *m)
{
    for (int r = m->radku - 1; r >= 0; r--) {
        for (int s = r + 1; s < m->sloupcu - 1; s++) {
            m->prvek[r][m->sloupcu - 1] += m->prvek[r][s] * m->prvek[s][m->sloupcu - 1];
        }

        m->prvek[r][m->sloupcu - 1] /= m->prvek[r][r];
    }
}

/** \brief Provede zpětný chod GJEM.
 *
 * Hodnoty neznámých nastaví do posledního sloupce rozšířené matice soustavy.
 *
 * \param m Tmatice* Ukazatel na rozšířenou matici soustavy.
 */
void gjemZpetny(Tmatice *m)
{
  // TODO: naprogramuj ji
  printf("Funkce gjemZpetny neni hotova.");
}

/** \brief Tiskne řešení soustavy rovnic, které je uloženo v posledním sloupci rozšířené matice soustavy.
 *
 * \param m Tmatice* Ukazatel na rozšířenou matici soustavy.
 */
void tiskReseni(Tmatice *m)
{
}

/** \brief Vyřeší upravenou soustavu rovnic.
 *
 * Zadání:
 * Pro řešení využij funkce z modulu matice.h a funkce gemPoPrimem, gjemPoPrimem, gemZpetny a gjemZpetny.
 * 1. Načti soubor s maticí.
 * 1a. Uprav ji do požadovaného tvaru pro zpětný chod.
 * 2. Otestuj zda jde o matici s jedním řešením po provedení přímého chodu GEM nebo GJEM.
 * 3. Vyřeš ji.
 * 4. Vypiš řešení soustavy pomocí funkce tiskReseni.
 */
void testZpetnyChod(char *jmenoSouboru)
{
  printf("==========================================\n");
  printf("Test pivotovani\n");

  FILE* f = fopen(jmenoSouboru, "r");
  if (f == NULL) {
    printf("nepovedlo se otevrit soubro");
    return;
  }

  Tmatice* matice = nactiMatici(f);
  if (matice == NULL) {
    printf("nepovedlo se nacist matici to me mrzi");
    return;
  }

  gemPrimy(matice);

  printf("pocet reseni: %i\n", gemPoPrimem(matice));

  gemZpetny(matice);

  tiskReseni(matice);

  fclose(f);
  uvolniMatici(matice);

  printf("==========================================\n");



}





/** Startovní bod programu. */
int main(void)
{
  // Co nepotřebuješ, si můžeš zakomentovat.

  srand(time(NULL));

  //testInit();
  //testFileRW("A.txt", NULL); // NULL -> bude zapisovat na stdout
  //testMult();

  //testPrimehoChodu("B.txt");          // otestuj i jiné soubory
  //testMaticePoPrimemChodu("D.txt");   // otestuj i jiné soubory
  testZpetnyChod("A.txt");            // otestuj i jiné soubory
  return EXIT_SUCCESS;
}
