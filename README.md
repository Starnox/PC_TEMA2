# Tema 2 PC. A Game of Scrabble

### Elev: Mihailescu Eduard-Florin
### Grupa: 312CB


#### Filosofie Generala
In scrierea codului am plecat de la ideea generala de modularizare, astfel
fiecare task are functia lui separata, iar fiecare idee un pic mai complexa
este implementata intr-o functie separata. Astfel sacrific un pic ideea de nu repeta
cod in favoarea unui cod stabil care ruleaza fiecare task independent (Daca pica unul
celalalte raman intacte). Comentarile sunt scrise in engleza pentru ca este mult mai
natural si este pastrat _flow-ul_ programului.

#### Functia main
Functia main am plasat-o la inceputul fisierului deoarece este punctul de plecare
al programului. Initial citesc cerinta pe care trebuie sa o rezolv dupa care
initializez tabla de joc cu o matrice de 15*15 plina cu caracterul ".". 
Folosindu-ma de instructiunea de decizie "switch" pentru a selecta taskul cerut.

#### Functii de citire
Enuntul a specificat clar ca nu avem voie sa citim datele cu functiile `scanf()` si
`fscanf()`, astfel, am ajuns la concluzia ca `fgets()` este varianta cea mai buna pe care o am
la dispozitie. Citesc linie cu linie si imi parsez singur datele, despartind in cuvinte
folosind `strtok()` si transformand in tipul intreg cu functia `atoi()`. Am modularizat
procesul de citire in functiile si am trimis variabilele prin "referinta" in specificul
C-ul pentru a putea folosi functiile oriunde am nevoie:
* `read_word(int *y, int *x, int *direction, char *word)` - care citeste un cuvant si modul in care acesta este plasat
* `read_n(int *n)` - citeste un singur numar n
* `read_x(char *XX)` - citeste un sir de 2 caractere

#### Functie de afisare
* `print_score(int score_player1, int score_player2)` - doar afisez cele doua variabile in formatul specificat

#### Functii de logica
* `insert_word(int y, int x, int direction, char word[])` - inserez in tabla de joc fiecare caracter al cuvantului respectand
directia specificata
* `calculate_multiplier(int y, int x, int direction, char word[], int has_xx, int ends_yy)` - pentru fiecare casuta ocupata de un caracter al cuvantului
verific daca este o casuta ce aduce bonus si daca este respectata conditia sirul de caractere
aferenta
* `calculate_score(char word[])` - parcurg fiecare caracter si adaug la suma punctajul corespunzator din vectorul `points_for_letter[26]` hardcodat la inceputul fisierului
* `check_substring(char word[], char XX[])` - verific daca sirul `XX` se regaseste in `WORD`
* `check_substring_ending(char word[], char XX[])` - verific daca sirul `WORD` se termina in `XX`

* `mark_word(char word[], int used_words[])` - Iterez prin fiecare cuvant din lista data si il compar cu `WORD`.
Daca sunt egale il marchez pe `WORD` in vectorul `used_words[]` pentru a stii ca este folosit.
* `try_place_word(int word_index, int used_words[])` - Parcurg fiecare casuta din tabla de joc, iar daca in aceea
casuta se afla primul caracter din cuvantul situat pe pozitia `word_index` atunci verific atat pe orizontala cat si pe verticala daca il pot plasa incepand cu casuta respectiva. Daca il pot
plasa, atunci o si fac si returnez 1 semnaland ca functia a avut loc cu succes
* `calculate_optimal_placement(int word_index, int has_xx, int ends_yy, int *aux_score,int *aux_y, int *aux_x, int *aux_direction, int used_words[])` - Functia este foarte asemanatoare cu cea de dinainte
insa de data aceasta nu ma opresc daca gasesc o pozitie valida, ci returnez prin variabilele
date ca parametrii amplasarea optima a cuvantului situat la indicele `word_index`.
* `initialise_board()`- folosesc functia `memset()` pentru a umple tabla de joc cu caracterul '.'

#### Functii de rezolvare ale taskurilor
* `solve0()` - doar afisez tabla de joc cu functia `print_board(playing_board)` (tabla a fost
initializata in `main`)
* `solve1()` - citesc fiecare cuvant in parte cu `read_word()`, il inserez cu `insert_word()`
si la sfarsit afisez tabla cu `print_board()`
* `solve2()` -  citesc fiecare cuvant in parte cu `read_word()`, il inserez cu `insert_word()`
si in functie de paritatea indexului cu care iterez adaug alternativ puncte la scorul fiecarui jucator folosindu-ma de `calculate_score()`
* `solve3()` - la fel ca la `solve2()`, doar ca la fiecare tura stabilesc si bonusul verificand
conditiile pentru XX si YY cu `check_substring()` si `check_substring_ending()` pe care le folosesc dupa in `calculate_multiplier()`
* `solve4()` Citesc fiecare cuvant in parte cu `read_word()`, il inserez cu `insert_word()` si il marchez ca "folosit" prin functia `mark_word()`. Dupa care, parcurg fiecare cuvant din lista
data in ordine si incerc sa il plasez pe tabla de joc, iar daca reusesc, ies din instructiune
si afisez tabla cu `print_board()`
* `solve5()` Citesc fiecare cuvant in parte cu `read_word()`, il inserez cu `insert_word()`, il marchez ca "folosit" prin functia `mark_word()` si de data aceasta calculez si punctajul pentru fiecare jucator tinand cont de bonusuri (procedeul este acelasi ca la `solve3()`). Dupa care, 
parcurg fiecare cuvant din lista si marchez punctajul maxim pe care acesta il poate aduce cu ajutorul functie `calculate_optimal_placement()`. Daca acest punctaj este cel mai mare pe care l-am gasit pana acum, il retin, iar daca este egal cu un altul gasit anterior verific daca
pozitionarea acestuia are un indice mai mix pe x si pe y. Daca are, atunci acesta va fi noul cuvant salvat momentan. Dupa ce am parcurs toate cuvinte, verific daca scorul maxim obtinut aduce victoria jucatorului 2 -> daca da, atunci plasez cuvantul cu `insert_word()` si afisez,
daca nu, afisez "Fail!"
* `solve6()` Codul de aici este foarte asemantor cu cel de la `solve5()`, doar ca de data aceasta fiecare mutare a jucatorului 2 o fac folosind functia `calculate_optimal_placement()` 






 