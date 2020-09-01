Proiect Arhipelag
====================================================================================================================================
Programul este alcatuit din:
=================================================
Makefile:
Functia build care compileaza fisierele main.c si functions.c si are ca fisier de output executabilul avion
De asemenea, functia build ruleaza executabilul avion cu parametrii date.in si rezultate.out, acestea fiind fisiere text de intrare si de iesire
Functia clean:
Sterge fisierele .out si executabilul
=================================================
Functions.h (header file):
Acest fisier contine toate structurile folosite in interiorul programului si de asemenea toate head-urile functiilor apelate
=================================================
Main.c:
Acest fisier contine functia int main cu parametrii argc si argv
In aceasta functie se deschid fisierele de intrare si de iesire, se declara variabile aferente rezolvarii problemelor si se apeleaza functiile necesare
de citire, creare graf si proiectare.
=================================================
Functions.c
Acest fisier contine toate functiile necesare
Functia Read citeste intr-un vector de tip structura toate datele, returnand la final vectorul modificat
Functia create creeaza graful necesar pe baza datelor citite anterior in vectorul structura
Functia Proiectare se comporta ca un hub al cerintelor, aceasta apeland fiecare functie aferenta rezolvarii cerintei respective
Functia Dijkstra se bazeaza pe algoritmul lui dijkstra si rezolva problemele impuse de sirurile de caractere "drum_zbor", "timp_zbor" si "min_zbor"
====================================================================================================================================
Input:

In fisierul date.in se vor gasi informatii sub urmatoarea structura:
1) Numar de insule - n
2) Pe urmatoarele n linii se vor descrie insulele cu resursele proprii.
Nume insula
Numar resurse –m
Tip_1 resursa si cantitate
Tip_2 resursa si cantitate
…
Tip_m resursa si cantitate
Numar conexiuni – p (se vor prezenta conexiunile intre insulele arhipelagului si durate de zbor prestabilite).
Pe urmatoarele p linii se vor afisa conexiunile intre insule: IslandY - IslandZ durata_zbor
 conexiune X Y
 adauga_zbor X Y cost
 anulare_zbor X Y
 legatura X
 alte_cerinte
====================================================================================================================================
Mod de functionare:

* Dupa citirea insulelor si conexiunilor, fisierul de input va contine partea de proiectare (modificarea traseelor intre insule pentru ziua curenta) 
si cea de analiza a datelor pentru distribuirea optima a resurselor.
* Avand in vedere dezvoltarea continua a arhipelagului in fiecare zi si intentia acestora de automatizare a distribuirii resurselor catre celalalte 
insule in nevoie, se comunica niste modificari generale.
* Programul citeste succesiv datele din fisierul date.in
* Atunci cand intalneste sirul de caractere "conexiune" acesta apeleaza functia conexiune care stabileste daca exista conexiune intre insulele X si Y
si afiseaza OK daca exista si NO in caz contrar
* Atunci cand intalneste sirul de caractere "legatura" acesta apeleaza functia legatura care stabileste existenta legaturii directe a insulei X cu celelalte din arhipelag,
iar in caz contrar nu se afiseaza nimic
* Atunci cand intalneste sirul de caractere "adauga_zbor" acesta apeleaza functia adauga_zbor prin care se adauga un drum direct de durata "cost" intre insulele X si Y
* Atunci cand intalneste sirul de caractere "anulare_zbor" acesta apeleaza functia anulare_zbor prin care se sterge drumul direct intre insulele X si Y
* Atunci cand intalneste sirul de caractere "max_resurse" acesta apeleaza functia max_resurse care afiseaza numarul de resurse distincte pe tot arhipelagul, urmat de numele
resurselor separate printr-un spatiu in ordine lexicografica
* Atunci cand intalneste sirul de caractere "max_cantitate" acesta apeleaza functia max_cantitate care afiseaza insula sau insulele cu cantitatea cea mai mare de resursa
disponibila
* Atunci cand intalneste sirul de caractere "drum_zbor" se apeleaza functia drum_zbor care la randul ei, folosindu-se de Algoritmul lui Dijkstra afiseaza drumul cel mai scurt
de la insula X la insula Y, iar in cazul in care nu exista drum, se afiseaza NO
* In contextul minimizarii timpului de zbor intre doua insule, se vor analiza doua scenarii:
* Scenariul "timp_zbor" care afiseaza durata minima in conditii de distribuire instanta, iar in cazul in care nu se poate determina timpul zborului, se afiseaza INF
* Scenariul "min_zbor" prevede stationarea 15 minute pe fiecare insula la fiecare distribuire din cauza aglomeratiei