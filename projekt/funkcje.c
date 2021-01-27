#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "funkcje.h"

plansza* wyzeruj_plansze(){
    plansza* A = (plansza*) malloc(sizeof(plansza));
    for(int i = 0; i < wiersze; i++){
        for(int j = 0; j < kolumny; j++){
            A->pola[i][j] = ' ';
        }
    }
    A->wolne = wiersze*kolumny;
    A->czyj_ruch = czerwone;
    A->max_czerwone = 0;
    A->max_zolte = 0;

    return A;
}

void free_decyzja(Ocena* decyzja1, Ocena* decyzja2, Ocena* decyzja3){
    free(decyzja1);
    free(decyzja2);
    free(decyzja3);
}

void bot(plansza* A){
    Ocena* decyzja1 = minimax(A, 1, -1000000, 1000000);
    printf("po decyzja1\n");
    Ocena* decyzja2 = minimax(A, 2, -1000000, 1000000);
    printf("po decyzja2\n");
    Ocena* decyzja3 = minimax(A, 3, -1000000, 1000000);
    printf("po decyzja3\n");

    printf("po minimaksie\n");

    if(decyzja2->value < decyzja3->value)
    {
        if(decyzja1->value < decyzja2->value)
        {
            wrzuc_zeton(A, decyzja1->kolumna);
        }
        else
        {
            wrzuc_zeton(A, decyzja2->kolumna);
        }   
    }
    else
        wrzuc_zeton(A, decyzja3->kolumna);

    free_decyzja(decyzja1, decyzja2, decyzja3);
}

int gracz(plansza* A){
    char ruch[10];

    fgets(ruch, 10, stdin);
    strtok(ruch, "\n");
    if(strcmp(ruch, "quit") == 0)
        return -1;
    else if(atoi(ruch) > kolumny){
        while (atoi(ruch) > kolumny){
            printf("maksymalny numer kolumny to %d\n", kolumny);
            fgets(ruch, 10, stdin);
        }
    }

    wrzuc_zeton(A, atoi(ruch));
    return 0;
}

void print_info(plansza* A){
    Ocena* eval = ocena(A);
    int* dozwolon_ruch = dozwolony_ruch(A);

    printf("maks niezablokowany czerwony: [%d][%d], %d, %s, blok: %d\n", maks_nieblok('c', A).wiersz_p + 1, maks_nieblok('c', A).kolumna_p + 1, maks_nieblok('c', A).dlugosc, maks_nieblok('c', A).typ, maks_nieblok('c', A).blok);
    printf("maks niezablokowany zolty: [%d][%d], %d, %s, blok: %d\n", maks_nieblok('z', A).wiersz_p + 1, maks_nieblok('z', A).kolumna_p + 1, maks_nieblok('z', A).dlugosc, maks_nieblok('z', A).typ, maks_nieblok('z', A).blok);
    printf("ocena: %d\n", eval->value);
    printf("dozwolone ruchy: ");
    for(int i = 0; i < kolumny; i++){
        printf("%d, ", dozwolon_ruch[i]);
    }
    printf("\n");

    free(eval);
    free(dozwolon_ruch);
}

int czy_zablokowany(plansza *A, linia l){ //0 - niezablokowany, 1 - zablokowany z jednej strony, 2 - zablokowany z dwoch stron
    float czy_blok = 0; //niezablokowany
    if(strcmp(l.typ, "pion") == 0){
        if(l.wiersz_p == 0) //jezeli l zaczyna sie od gory planszy
            czy_blok ++;
        else{
            if(A->pola[l.wiersz_p - 1][l.kolumna_p] != ' ')
                czy_blok++;
        }
        if(l.wiersz_p + l.dlugosc == wiersze){ //jezeli l konczy sie na samym dole planszy
            czy_blok ++;
        }
        else{
            if(A->pola[l.wiersz_p + l.dlugosc][l.kolumna_p] != ' ')
                czy_blok ++;
        }
        return czy_blok;
    }
    else if(strcmp(l.typ, "poziom") == 0){
            if(l.kolumna_p == 0) //jezeli l zaczyna sie po lewej
            czy_blok ++;
        else{
            if(A->pola[l.wiersz_p][l.kolumna_p - 1] != ' ')
                czy_blok ++;
        }
        if(l.kolumna_p + l.dlugosc == kolumny) //jezeli l konczy sie na ostatniej kolumnie (prawej)
            czy_blok ++;
        else{
            if(A->pola[l.wiersz_p][l.kolumna_p + l.dlugosc] != ' ')
                czy_blok ++;
        }
        return czy_blok;
    }
    else if(strcmp(l.typ, "skos1") == 0){  
        if(l.wiersz_p == 0 || l.kolumna_p == 0) //jezeli zaczyna sie w lewej kolumnie albo w pierwszym wierszu (lewy gorny róg)
            czy_blok ++;
        else{
            if(A->pola[l.wiersz_p - 1][l.kolumna_p - 1] != ' ')
                czy_blok ++;
        }
        if(l.wiersz_p + l.dlugosc == wiersze || l.kolumna_p + l.dlugosc == kolumny) //jezeli konczy sie w ostatniej kolumnie albo ostatnim wierszu (lewy dolny róg)
            czy_blok ++;
        else{
            if(A->pola[l.wiersz_p + l.dlugosc][l.kolumna_p + l.dlugosc] != ' ')
                czy_blok ++;
        }
        return czy_blok;
    }
    else if(strcmp(l.typ, "skos2") == 0){
        if(l.wiersz_p == 0 || l.kolumna_p == kolumny - 1) //jezeli zaczyna sie w pierwsyzm wierszu albo ostatniej kolumnie (prawy gorny róg)
            czy_blok ++;
        else{
            if(A->pola[l.wiersz_p - 1][l.kolumna_p + 1] != ' ')
                czy_blok ++;
        }
        if(l.wiersz_p + l.dlugosc == wiersze || l.kolumna_p - l.dlugosc + 1 == 0) //jezeli konczy sie w pierwszej kolumnie albo ostatnim wierszu (lewy dolny róg)
            czy_blok ++;
        else{
            if(A->pola[l.wiersz_p + l.dlugosc][l.kolumna_p - l.dlugosc] != ' ')
                czy_blok ++;
        }
        return czy_blok;
    }
    return -1;
}

linia pion(int wiersz, int kolumna, plansza *A){
    linia x;
    int k = 0;
    int maks = 0;
    int kiedy_pierwszy = 0; //zapisac chce pozycje kiedy bedzie pierwszy element
    for(int i = 0; i < wiersze; i++){
        if(A->pola[i][kolumna] == A->pola[wiersz][kolumna]){
            k++;
            if(k > maks)
                maks = k;
            kiedy_pierwszy ++;
            if(kiedy_pierwszy == 1){
                x.wiersz_p = i;
            }
        }
        else{
            k = 0;
            kiedy_pierwszy = 0;
        }
    }
    x.dlugosc = maks;
    x.kolumna_p = kolumna;
    x.typ = "pion";
    x.blok = czy_zablokowany(A, x);

    return x;
}

linia poziom(int wiersz, int kolumna, plansza *A){
    linia x;
    int k = 0;
    int maks = 0;
    int kiedy_pierwszy = 0;
    for(int j = 0; j < kolumny; j++){
        if(A->pola[wiersz][j] == A->pola[wiersz][kolumna]){
            k++;
            if(k > maks)
                maks = k;
            kiedy_pierwszy ++;
            if(kiedy_pierwszy == 1)
                x.kolumna_p = j;
        }
        else{
            k = 0;
            kiedy_pierwszy = 0;
        }
    }
    x.dlugosc = maks;
    x.wiersz_p = wiersz;
    x.typ = "poziom";
    x.blok = czy_zablokowany(A, x);

    return x;
}

linia skos1(int wiersz, int kolumna, plansza *A){ //zwraca najwieksza ilosc zetonow o kolorze jak na pozycji [wiersz][kolumna] po skosie
    linia x;
    int k = 0;
    int maks = 0;
    int kiedy_poczatek = 0;
    //pierwsza przekatna zawierajaca element [wiersz][kolumna]:
    int wiersz_p = wiersz;//wiersz poczatku przekatnej
    int kolumna_p = kolumna;//kolumna poczatku przekatnej
    while(wiersz_p != 0 && kolumna_p != 0){
        wiersz_p--;
        kolumna_p--;
    }
    while(wiersz_p != wiersze && kolumna_p != kolumny){
        if(A->pola[wiersz_p][kolumna_p] == A->pola[wiersz][kolumna]){
            k++;
            if(k > maks)
                maks = k;
            kiedy_poczatek++;
            if(kiedy_poczatek == 1){
                x.wiersz_p = wiersz_p;
                x.kolumna_p = kolumna_p;
            }
        }
        else{
            k = 0;
            kiedy_poczatek = 0;
        }

        wiersz_p ++;
        kolumna_p ++;
    }
    x.dlugosc = maks;
    x.typ = "skos1";
    x.blok = czy_zablokowany(A, x);

    return x;
}

linia skos2(int wiersz, int kolumna, plansza *A){ //druga przekatna zawierajaca element [wiersz][kolumna]
    linia x;
    int k = 0;
    int maks = 0;
    int kiedy_poczatek = 0;
    int wiersz_p = wiersz;//wiersz poczatku przekatnej
    int kolumna_p = kolumna;//kolumna poczatku przekatnej

    while(wiersz_p != 0 && kolumna_p != kolumny-1){
        wiersz_p--;
        kolumna_p++;
    }
    while(wiersz_p != wiersze && kolumna_p != -1){
        if(A->pola[wiersz_p][kolumna_p] == A->pola[wiersz][kolumna]){
            k++;
            if(k > maks)
                maks = k;
            kiedy_poczatek++;
            if(kiedy_poczatek == 1){
                x.wiersz_p = wiersz_p;
                x.kolumna_p = kolumna_p;
            }

        }
        else{
            k = 0;
            kiedy_poczatek = 0;
        }

        wiersz_p ++;
        kolumna_p --;
    }
    x.dlugosc = maks;
    x.typ = "skos2";
    x.blok = czy_zablokowany(A, x);

    return x;
}

//uwzglednia blokowanie (chcemy wypisac taki maks ktory nie jest calkowicie zablokowany)
linia maks_nieblok(char a, plansza *A){ //wyswietla poczatek i dlugosc i typ i blok(na przyklad [1][5], dlugosc 3, typ skos, blok 1/blok 0)
    linia maks;
    maks.wiersz_p = 0;
    maks.kolumna_p = 0;
    maks.dlugosc = 0;
    maks.blok = 2;
    for(int i = 0; i < wiersze; i++){
        for(int j = 0; j < kolumny; j++){
            if(A->pola[i][j] == a){
                if(pion(i, j, A).dlugosc >= maks.dlugosc && pion(i, j, A).blok < 2)
                {
                    if(pion(i, j, A).dlugosc == maks.dlugosc && pion(i, j, A).blok < maks.blok)
                        maks = pion(i, j, A);
                    else if(pion(i, j, A).dlugosc > maks.dlugosc)
                        maks = pion(i, j, A);
                }
                if(poziom(i, j, A).dlugosc >= maks.dlugosc && poziom(i, j, A).blok < 2)
                {
                    if(poziom(i, j, A).dlugosc == maks.dlugosc && poziom(i, j, A).blok < maks.blok)
                        maks = poziom(i, j, A);
                    else if(poziom(i, j, A).dlugosc > maks.dlugosc)
                        maks = poziom(i, j, A);
                }
                if(skos1(i, j, A).dlugosc >= maks.dlugosc && skos1(i, j, A).blok < 2)
                {
                    if(skos1(i, j, A).dlugosc == maks.dlugosc && skos1(i, j, A).blok < maks.blok)
                        maks = skos1(i, j, A);
                    else if(skos1(i, j, A).dlugosc > maks.dlugosc)
                        maks = skos1(i, j, A);
                }
                if(skos2(i, j, A).dlugosc >= maks.dlugosc && skos2(i, j, A).blok < 2)
                {
                    if(skos2(i, j, A).dlugosc == maks.dlugosc && skos2(i, j, A).blok < maks.blok)
                        maks = skos2(i, j, A);
                    else if(skos2(i, j, A).dlugosc > maks.dlugosc)
                        maks = skos2(i, j, A);
                }
            }
        }
    }
    return maks;
}

//ogolnie maksymalne
linia maks(char a, plansza *A){
    linia maks;
    maks.wiersz_p = 0;
    maks.kolumna_p = 0;
    maks.dlugosc = 0;
    for(int i = 0; i < wiersze; i++){
        for(int j = 0; j < kolumny; j++){
            if(A->pola[i][j] == a){
                if(pion(i, j, A).dlugosc > maks.dlugosc)
                {
                    maks = pion(i, j, A);
                }
                if(poziom(i, j, A).dlugosc > maks.dlugosc)
                {
                    maks = poziom(i, j, A);
                }
                if(skos1(i, j, A).dlugosc > maks.dlugosc)
                {
                    maks = skos1(i, j, A);
                }
                if(skos2(i, j, A).dlugosc > maks.dlugosc)
                {
                    maks = skos2(i, j, A);
                }
            }
        }
    }
    return maks;
}

void delay(int ile_sekund) 
{ 
    int milli_seconds = 1000 * ile_sekund; 
  
    clock_t start_time = clock(); 

    while (clock() < start_time + milli_seconds) 
        ; 
} 

void wyswietl(plansza *A){ //wyswietlanie statycznej planszy
    printf("  ");
    for(int j = 0; j < kolumny; j++){
            printf("%4d", j+1); //wypisuje nr kolumny
    }
    printf("\n");
    for(int i = 0; i < wiersze; i++){
        printf("  ");
        for(int j = 0; j < kolumny; j++){
            printf("+---"); //wypisuje rozdzielenie miedzy wierszami
        }
        printf("+\n%2d", i+1); //wypisuje numer wiersza
        for(int j = 0; j < kolumny; j++){
            //printf("|%c", A->pola[i][j]); //wypisuje elementy w wierszu
            if(A->pola[i][j] == 'c'){
                printf("|");
                printf(ANSI_COLOR_RED);
                printf(" # ");
                printf(ANSI_COLOR_RESET);
            }
            else if(A->pola[i][j] == 'z'){
                printf("|");
                printf(ANSI_COLOR_YELLOW);
                printf(" # ");
                printf(ANSI_COLOR_RESET);
            }
            else if(A->pola[i][j] == ' '){
                printf("|");
                printf("   ");
            }
        }
        printf("|\n");
    }
    printf("  ");
    for(int j = 0; j < kolumny; j++){
        printf("+---"); //wypisuje rozdzielenie miedzy wierszami
    }
    printf("+\n\n");
}


void animacja(plansza *A, int kolumna){ //animacja wpadajacego zetonu
    int wiersz = 0;
    kolumna = kolumna - 1;
    plansza *kopia = skopiuj_plansze(A);
    system("@cls||clear"); //czysci terminal ubuntu
    while (A->pola[wiersz][kolumna] == ' '){
        kopia->pola[wiersz][kolumna] = A->czyj_ruch;
        wyswietl(kopia);
        delay(1500/wiersze);
        system("@cls||clear");
        kopia->pola[wiersz][kolumna] = ' ';
        wiersz++;
    }
    free(kopia);
}

void wrzuc_zeton(plansza *A, int kolumna){
    wyswietl(A); //wyswietla na chwile tą plansze przed wrzuceniem zetonu
    animacja(A, kolumna); //wyswietla animacje wrzucania zetonu 

    int i;
    
    if(A->pola[0][kolumna-1] != ' '){
        printf("Zajete!!\n");
        goto end; //zeby nie czyscilo terminala juz bo wtedy znika napis ze zajete
    }
    else{
    for(i = 0; i < wiersze; i++){
        if(A->pola[i+1][kolumna-1] != ' ')
            break;
    }
    if(i >= wiersze-1)
        A->pola[wiersze-1][kolumna-1] = A->czyj_ruch;
    else
        A->pola[i][kolumna-1] = A->czyj_ruch;

    A->wolne -= 1;
    if(A->czyj_ruch == zolte)
        A->czyj_ruch = czerwone;
    else if(A->czyj_ruch == czerwone)
        A->czyj_ruch = zolte;
    }
    A->max_czerwone = maks('c', A).dlugosc;
    A->max_zolte = maks('z', A).dlugosc;

    system("@cls||clear"); //czysci terminal ubuntu
    end:
    wyswietl(A); //wyswietla stan koncowy juz jak zeton wpadnie na sam dol
    if(A->max_czerwone < wygrywa && A->max_zolte < wygrywa)
    {
        if(A->czyj_ruch == zolte)
        {
            printf(ANSI_COLOR_YELLOW);
            printf("ruch zoltego\n");
            printf(ANSI_COLOR_RESET);
        }
        else if(A->czyj_ruch == czerwone)
        {
            printf(ANSI_COLOR_RED);
            printf("ruch czerwonego\n");
            printf(ANSI_COLOR_RESET);
        }
    }
}

int wrzuc_zeton_bez_animacji(plansza *A, int kolumna){
    int i;
    
    if(A->pola[0][kolumna-1] != ' '){
        return -1;
    }
    else{
        for(i = 0; i < wiersze; i++){
            if(A->pola[i+1][kolumna-1] != ' ')
                break;
        }
        if(i >= wiersze-1)
            A->pola[wiersze-1][kolumna-1] = A->czyj_ruch;
        else
            A->pola[i][kolumna-1] = A->czyj_ruch;

        A->wolne -= 1;
        if(A->czyj_ruch == zolte)
            A->czyj_ruch = czerwone;
        else if(A->czyj_ruch == czerwone)
            A->czyj_ruch = zolte;
    }
    
    A->max_czerwone = maks('c', A).dlugosc;
    A->max_zolte = maks('z', A).dlugosc;

    return 0;
}

void wykonaj_ruch(plansza *A, int kolumna){
    int i = 0;
    if(A->pola[0][kolumna-1] == ' ')
    {
        for(i = 0; i < wiersze; i++){
            if(A->pola[i+1][kolumna-1] != ' ')
                break;
        }
        if(i >= wiersze-1)
            A->pola[wiersze-1][kolumna-1] = A->czyj_ruch;
        else
            A->pola[i][kolumna-1] = A->czyj_ruch;

        A->wolne -= 1;
        if(A->czyj_ruch == zolte)
            A->czyj_ruch = czerwone;
        else if(A->czyj_ruch == czerwone)
            A->czyj_ruch = zolte;
    }
    A->max_czerwone = maks('c', A).dlugosc;
    A->max_zolte = maks('z', A).dlugosc;
}

int* dozwolony_ruch(plansza *A) //wypisze 1 przy kolumnie do ktorej mozna wrzucic
{   
    int *ruchy = calloc (kolumny, sizeof (int));

    for (int j=0; j<kolumny ;j++)
    {    
        if (A->pola[0][j]==' ')
            ruchy[j] = 1;
    }
    return ruchy;
}

void s_to_l(char* a){
    for(int i = 0; i < strlen(a); i++){
        if((int)(a[i]) > 96 && (int)(a[i]) < 123)
            printf("%c", (char)(((int)a[i]) - 32));
        else
            printf("%c", a[i]);
    }
    printf("\n");
}

void animacja_tekstu(char *napis){
    for(int i = 0; i < strlen(napis); i++){
        for(int j = 0; j < strlen(napis); j++){
            if(j != i)
                printf("%c", ' ');
            else
                printf("%c", napis[i]);
        }
        printf("\n");
        for(int j = 0; j < strlen(napis); j++){
            if(j != i)
                printf("%c", napis[j]);
            else
                printf("%c", ' ');
        }
        printf("\n");

        delay(100);
        system("@cls||clear");
    }

    printf("\n%s\n", napis);
    delay(300);
    system("@cls||clear");

    //i w druga strone
    for(int i = strlen(napis) - 1; i >= 0; i--){
        for(int j = 0; j < strlen(napis); j++){
            if(j != i)
                printf("%c", ' ');
            else
                printf("%c", napis[i]);
        }
        printf("\n");
        for(int j = 0; j < strlen(napis); j++){
            if(j != i)
                printf("%c", napis[j]);
            else
                printf("%c", ' ');
        }
        printf("\n");

        delay(200);
        system("@cls||clear");
    }
    
    printf("\n%s\n", napis);
    delay(300);
    system("@cls||clear");

    //na zmiane duzy i maly
    for(int i = 0; i < 5; i++){
        if(i % 2 == 0){
            printf("\n");
            s_to_l(napis);
        }
        else{
            printf("\n");
            printf("%s\n", napis);
        }
        delay(500);
        system("@cls||clear");
    }

    printf("\n%s\n", napis);
}

Ocena* ocena(plansza *A) //zwraca ocene aktualnego stanu gry. Dotyczy tylko jednego momentu w grze (w konkretnym ustawieniu zetonow)
{
    Ocena* wynik = calloc(1, sizeof(Ocena));
    int pkt_czerwone = 0;
    int pkt_zolte = 0; //jakies punkty po jakich bedziemy oceniac jak im idzie (w jakiej sa sytuacji)

    pkt_czerwone = maks_nieblok('c', A).dlugosc * maks_nieblok('c', A).dlugosc * (2-maks_nieblok('c', A).blok); //kiedy blok = 0 to warte sa wiecej niz kiedy blok = 1
    pkt_zolte = maks_nieblok('z', A).dlugosc * maks_nieblok('z', A).dlugosc * (2-maks_nieblok('z', A).blok);

    if(strcmp(maks_nieblok('c', A).typ, "pion") == 0){
        pkt_czerwone += 1;
    }

    if(strcmp(maks_nieblok('z', A).typ, "pion") == 0){
        pkt_zolte += 1;
    }
    
    if(A->max_czerwone >= wygrywa)
        pkt_czerwone += 1000;
    if(A->max_zolte >= wygrywa)
        pkt_zolte += 1000;

    wynik->value = pkt_czerwone - pkt_zolte; //jezeli ocena > 0 to czerwony ma lepiej, a jak ocena < 0 to zolty ma lepiej!
    //co z kolumna?

    return wynik;
}

plansza* skopiuj_plansze(plansza *A){
    plansza* kopia;
    kopia = wyzeruj_plansze();

    for(int i=0; i<wiersze; i++){
        for(int j = 0; j < kolumny; j++){
            kopia->pola[i][j] = A->pola[i][j];
        }
    }

    kopia->czyj_ruch = A->czyj_ruch;
    kopia->max_czerwone = A->max_czerwone;
    kopia->max_zolte = A->max_zolte;
    kopia->wolne = A->wolne;

    return kopia;
}

Ocena* minimax(plansza *A, int glebokosc, long int a, long int b){
    printf("minimax\n");
    Ocena* eval;
    int max_eval, min_eval;
    Ocena* wynik = ocena(A);
    plansza* kopia;
    int* bufor;
    if(glebokosc == 0 || A->max_czerwone >= wygrywa || A->max_zolte >= wygrywa){
        return wynik;
    }

    else if(A->czyj_ruch == 'c'){ //chcemy maks ocene dla czerwonych
        max_eval = -1000000;
        for(int i = 0; i < kolumny; i++){ //dla wszystkich mozliwych ruchow
            kopia = skopiuj_plansze(A);
            bufor = dozwolony_ruch(kopia);
            if(bufor[i] == 1){
                wrzuc_zeton_bez_animacji(kopia, i + 1); //dozwolony ruch zwraca od 0 do 6, a wrzuc zeton bierze od 1 do 7 wiec trzeba +1
                eval = minimax(kopia, glebokosc - 1, a, b);
                if(eval->value > max_eval){
                    max_eval = eval->value;
                    wynik->value = max_eval;
                    wynik->kolumna = i + 1; //zwracamy w formacie 1-7 kolumne (numerujemy od 1, a nie od 0)
                }
                if(a < eval->value)
                    a = eval->value;
                if(b <= a){
                    free(eval);
                    free(kopia);
                    free(bufor);
                    break;
                }
                free(eval);
                free(kopia);
                free(bufor);
            }
            else{
                free(kopia);
                free(bufor);
            }
        }
        return wynik;
    }
    else if(A->czyj_ruch == 'z'){ //chcemy min ocene dla zoltych
        min_eval = 100000;  
        for(int i = 0; i < kolumny; i++){
            kopia = skopiuj_plansze(A);
            bufor = dozwolony_ruch(kopia);
            if(bufor[i] == 1){
                wrzuc_zeton_bez_animacji(kopia, i + 1);
                eval = minimax(kopia, glebokosc - 1, a, b);
                if(eval->value < min_eval){
                    min_eval = eval->value;
                    wynik->value = min_eval;
                    wynik->kolumna = i + 1;
                }
                if(b > eval->value)
                    b = eval->value;
                if(b <= a){
                    free(eval);
                    free(kopia);
                    free(bufor);
                    break;
                }
                free(eval);
                free(kopia);
                free(bufor);
            }
            else{
                free(kopia);
                free(bufor);
            }
        }
        return wynik;
    }
}