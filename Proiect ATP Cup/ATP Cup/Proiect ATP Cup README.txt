Proiect Tenis ATP Cup
====================================================================================================================================
Acest program a fost creat din dorinta de a automatiza desfasurarea turneului.
In acest scop au fost create fisierele:
1) date.in -> contine date despre numarul tarilor participante, numele tarii, numarul de jucatori al lotului si nume, prenume si scor personal pentru fiecare jucator
2) cerinte.in -> contine 5 cifre de 0 sau 1, valorile acestea hotarand care dintre cerintele de la 1 la 5 vor fi rezolvate
3) functions.c -> contine toate functiile necesare pentru automatizarea desfasurarii turneului
4) functions.h -> fisierul header contine header-ul tuturor functiilor folosite in program si structurile necesare
5) main.c -> fisierul main
6) Makefile -> fisierul Makefile prin care rulam tot programul din bash
====================================================================================================================================
Mod de functionare:

* Se creeaza o stiva dublu inlantuita, circulara, cu santinela, pentru stocarea tarilor participante
* Din lista respectiva se elimina tari pana cand numarul lor devine cea mai mare putere a lui 2 posibila, iar eliminarea se face dupa criteriul:
se elimina tara al carei scor initial este minim, scorul initial reprezentand media aritmetica a scorurilor personale ale jucatorilor din lotul tarii respective,
iar in cazul in care pentru ultima eliminare din lista exista mai multe tari cu acelasi scor initial minim, este eliminata prima tara cu scorul initial minim gasita
in parcurgerea listei pornind de la santinela
* Se creeaza o stiva in care sunt adaugate toate tarile ramase in turneu
* Din stiva se scot succesiv cate 2 tari intre care se joaca meciurile, iar procedeul se repeta pana cand stiva se goleste si se vor adauga intr-o coada care contine
meciurile dintre jucatori
* Fiecare jucator din lotul primei tari joaca succesiv cu fiecare jucator din cel de-al doilea lot, al doilea jucator din lotul primei tari
cu jucatorii din cel de-al doilea, pana cand meciurile vor fi epuizate. Jucatorul cu scorul personal mai mare castiga, primind 5 puncte la scorul personal, iar tara
acestuia 3 puncte la scorul local. In caz de egalitate, fiecarui jucator i se adauga cate 2 puncte la scorul personal, iar fiecare tara primeste 1 punct la scorul local
* La finalul partidei, scorul local se adauga la scorul global al fiecarei tari, castigatoare fiind tara cu scorul local mai mare, iar in caz de egalitate, castigatoare este
tara cu jucatorul cu scorul personal mai mare
* Se creeaza o stiva numita WINNER in care se adauga toate tarile castigatoare in urma meciurilor
* Cand stiva initiala devine goala, tarile din stiva WINNER sunt transferate in stiva initiala si se repeta tot procesul pana cand in stiva WINNER ramane o singura tara
* Atunci cand raman 4 tari in turneu, se creeaza un arbone binar de cautare BST in care se vor adauga jucatorii celor 4 tari ramase, in functie de scorul personal, iar in
cazul in care exista 2 jucatori cu acelasi scor, va fi adaugat jucatorul al carui nume este mai mic din punct de vedere lexicografic
* In fisierul cerinte.in se afla numele a 2 jucatori, evident al unor jucatori din cele 4 tari ramase, in final afisandu-se numarul jucatorilor care se gasesc in arbore
intre cei 2 jucatori al caror nume se gaseste in fisierul mentionat anterior
