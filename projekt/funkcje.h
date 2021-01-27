#ifndef _funkcje_h
#define _funkcje_h

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[37m"

#define czerwone 'c'
#define zolte 'z'

#define wiersze 6
#define kolumny 7
#define wygrywa 4

typedef struct _plansza {
    char pola [wiersze][kolumny];
    char czyj_ruch; //pokazuje stan planszy i czyj ruch jest. Żetony wrzucane są od góry
    int max_czerwone;
    int max_zolte; //w pionie, poziomie albo skosie, bedzie wybieral najwieksze
    int wolne; //ile niezapelnionych miejsc. Jesli wolne = 0, a max_czerwone<wygrywa && max_zolte<wygrywa to remis
} plansza;

typedef struct _linia {
    int dlugosc;
    int wiersz_p;
    int kolumna_p; //wiersz_p, kolumna_p okresla pierwszy element nalezacy do tej linii
    char *typ; //"pion", "poziom", "skos1", "skos2"
    int blok; //blok = 0 - z obu stron wolne miejsca, blok = 1 - z jednej strony zablokowane, blok = 2 - z obu stron zablokowane
} linia;

typedef struct _Ocena {
    int value;
    int kolumna;
} Ocena;

plansza* wyzeruj_plansze();
void wyswietl(plansza *A);
linia maks_nieblok(char a, plansza *A);
linia pion(int wiersz, int kolumna, plansza *A);
linia poziom(int wiersz, int kolumna, plansza *A);
linia skos(int i, int j, plansza *A);
void wrzuc_zeton(plansza *A, int kolumna);
void animacja(plansza *A, int kolumna);
void delay(int ile_sekund);
int* dozwolony_ruch(plansza *A);
void s_to_l(char* a);
void animacja_tekstu(char *napis);
Ocena* ocena(plansza *A);
Ocena* minimax(plansza *A, int glebokosc, long int a, long int b);
void wykonaj_ruch(plansza *A, int kolumna);
int czy_zablokowany(plansza *A, linia maks);
linia maks(char a, plansza *A);
plansza* skopiuj_plansze(plansza *A);
int wrzuc_zeton_bez_animacji(plansza *A, int kolumna);
void free_decyzja(Ocena* decyzja1, Ocena* decyzja2, Ocena* decyzja3);
void print_info(plansza* A);
void bot(plansza* A);
int gracz(plansza* A);

#endif