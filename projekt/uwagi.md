Podzielić pliki:
1) main.c
2) pliki źródłowe i nagłówkowe:
    - mapa - przechowywanie,struktura (wraz z dx,dy) ,alokacja,zwalnianie,wpisywanie,wypisywanie do pliku i na ekranie 
    - komunikacja - zapytania do API
    - analiza_odpowiedzi (JSON) - przetwarzanie response z API, przetworzenie przez cJSON i zwrócenie dane w postaci strukturalnej (przerobić napis cJSON na strukture) w języku C z wyodrębnionymi wartościami zawartymi w response. 
        
        Podany przykład do interpretacji JSON na seminarium:
            struct resp_move * interpret_move(char *response)
            {
                resp_move *r = malloc(sizeof(resp_move));
                r->x=cJSON.getObjectIte
            }

    - logika - interpretacja jak jestesmy zlokalizowani, jakie są bloki obok, podejmuje decyzje co dalej (gdzie pójść może być losowe)

Stworzenie plików testujących (musi być inaczej obniżona ocena):
    Które zawierają tylko main gdzie sprawdzane są funkcje z plików .h, pozwala sprawdzić poprawność funkcji oraz wycieki pamięci
    -mapa_test.c (utworzenie mapy 5x5, zapamiętanie wartości przy pomocy offset(mapa,x,y))
    -komunikacja_test.c
    -analiza_odpowiedzi_test.c
    -logika_test.c

Budowanie mapy świata:

    Dynamiczna budowa mapy:(ok.19:50 na nagraniu do 44:10)
        Prealokowana tablica o wielkości 5x5, startowanie od środka tablicy
        Przemapowanie współrzędnych (podział na lokalne i serwerowe):
            Stworzenie Offsetu: 
                dx, dy 
                dla wygody zamiast offset (mapa,x,y) można zrobić offsetx/ox(mapa, x), offsety/oy(mapa,y) co przelicza współrzędne serwerowe na lokalne
        Dynamicznie alokowanie świata w momencie dojścia do krawędzi: 
            stworzenie nowej tablicy przez doklejenie 5 warstw (stałe chunki) i zaaktualizowanie dx i dy poprzez dodanie 5 (liczbe doklejonych warstw)

Eksplorowanie świata(ok. 44:10 na nagraniu do 01:11:00):

    Znajdowanie otoczki:

        1) move cały czas do przodu aż do ściany(zapisanie wartości x,y), obrót w prawo i move do przodu przy każdym kroku sprawdzanie czy da się w lewo   do momentu powrotu do punktu kiedy zetknęło się ze ścianą pierwszy raz.
        2) Przy każdym poprawnym wykonaniu Rotate_R i Rotate_L zwiększenie licznika R i L.
        3) Jeśli L-R=4 znaleziono wewnętrzną przedszkode a R większe w szukaniu obrysu mapy
        4) Następnie odwrót od ściany i move do momentu kolejnej ściany i powtórzenie 1) w celu odkrycia otoczki wypukłej

        W skrócie cały czas move rotate_L sprawdzenie czy da się do przodu jesli tak to move jesli nie to Rotate_R i move i od nowa 



