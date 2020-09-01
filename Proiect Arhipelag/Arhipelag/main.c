#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(int argc, char const *argv[])
{
    FILE *fdate = fopen(argv[1], "rt"); //deschidere fisier de intrare
    if(fdate == NULL)
    {
        printf("Eroare deschidere fisier fdate!");
        exit(1);
    }
    FILE *fout = fopen(argv[2], "wt"); //deschidere fisier de iesire
    if(fout == NULL)
    {
        printf("Eroare deschidere fisier fout!");
        exit(1);
    }
    int nr_insule, nr_conexiuni; //declararea variabilelor corespunzatoare pentru citirea numarului insulelor si a numarului de conexiuni
    fscanf(fdate, "%d", &nr_insule); //citirea numarului de insule
    Island *ReadVec = (Island*)malloc(nr_insule * sizeof(Island)); //declararea unui vector de tip Island folosit in citirea insulelor
    ReadVec = Read(nr_insule, fdate, ReadVec); //apelarea functiei Read pentru citire
    fscanf(fdate,"%d", &nr_conexiuni); //citirea numarului de conexiuni
    Graph *g = (Graph *) malloc (sizeof(Graph)); //declararea si alocarea de memorie pentru graf
    g = create(nr_conexiuni, fdate, g, nr_insule); //crearea grafului
    Proiectare(g, fdate, fout, ReadVec, nr_insule); //cerinta
}