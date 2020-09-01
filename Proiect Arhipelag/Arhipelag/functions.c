#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"


//functia de citire care citeste pe rand, intr o instructiune repetitiva cu pasii =  numarul insulelor, numele insulelor, numarul de resurse
//iar pentru fiecare resursa numele si cantitatea
Island* Read(int nr_insule, FILE *fdate, Island *ReadVec)
{
    for(int i = 0; i < nr_insule; i++)
    {
        ReadVec[i].nume = (char*)malloc(10 * sizeof(char));
        fscanf(fdate, "%s", ReadVec[i].nume);
        ReadVec[i].nume = (char*)realloc(ReadVec[i].nume, 
                                    sizeof(strlen(ReadVec[i].nume) + 1));

        fscanf(fdate, "%d", &ReadVec[i].nrResurse);
        ReadVec[i].inventarResurse = (Resursa*)malloc(ReadVec[i].nrResurse * sizeof(Resursa));
        for(int j = 0; j < ReadVec[i].nrResurse; j++)
        {
            ReadVec[i].inventarResurse[j].nume = (char*)malloc(10 * sizeof(char));
            fscanf(fdate, "%s %d", ReadVec[i].inventarResurse[j].nume, 
                                    &ReadVec[i].inventarResurse[j].cantitate);
            ReadVec[i].inventarResurse[j].nume = (char*)realloc(ReadVec[i].inventarResurse[j].nume,
                                sizeof(strlen(ReadVec[i].inventarResurse[j].nume) + 1));

        }

    }
   
    return ReadVec;
}

Graph * create (int nr_conexiuni, FILE *fdate, Graph *g, int nr_insule)
{
     // functia aloca spatiu pentru un graf si il initializeaza cu valori
    int i, j;
    if (g==NULL) 
    { 
        printf ( " no memory for this graph");
        return NULL;
    }
    g->nod = nr_insule;
    g->madiacenta = (int **) malloc(g->nod * sizeof(int*));
    for (i = 0; i < g->nod; i++) 
    g->madiacenta[i] = (int *) calloc(g->nod, sizeof(int)); //o initializez cu 0 
    

    if (g->madiacenta==NULL) 
    { 
        printf ( " no memory for this matrix");
        return NULL;
    }
    g->muchie = 0;



    for (i = 0; i < nr_conexiuni; i++)
    {
        int index1 = 0, index2 = 0, cost = 0;
        char *buffer1, *buffer2;
        buffer1 = (char*)malloc(20 * sizeof(char));
        buffer2 = (char*)malloc(20 * sizeof(char));
        fscanf(fdate, "%s", buffer1);

        fseek(fdate, 3, SEEK_CUR); //mut cursorul cu 3 spatii pentru a evita citirea " - "
        fscanf(fdate, "%s", buffer2);
        fscanf(fdate, "%d", &cost);

        index1 = atoi(&buffer1[6]); //prin functia atoi scot din numele insulelor indexurile necesare
        index2 = atoi(&buffer2[6]);

        g->madiacenta[index1-1][index2-1] = g->madiacenta[index2-1][index1-1] = cost; //indexurile le micsorez cu 1 deoarece o matrice are elementele de la 0 pana la n strict
        g->muchie += 2;

    }
    
    return g;
}

void printGraph(Graph *g)
{
    for (int i = 0; i < g->nod; i++) 
    {
    for (int j = 0; j < g->nod; j++)
        printf("%d ", g->madiacenta[i][j]);
        printf("\n");
    }
//am afisat matricea de adiacenta linie cu linie
}

//functia pentru rezolvarea cerintei "conexiune"
void FunctiaConexiune(char *conexiunea1, char *conexiunea2, Graph *g, FILE *fdate, FILE *fout)
{
    int index1, index2;
    fscanf(fdate, "%s", conexiunea1);
    fscanf(fdate, "%s", conexiunea2);
        conexiunea1 = (char*)realloc(conexiunea1, (strlen(conexiunea1) + 1) * sizeof(char));
        conexiunea2 = (char*)realloc(conexiunea2, (strlen(conexiunea2) + 1) * sizeof(char));
        index1 = atoi(&conexiunea1[6]); //aceeasi operatiune de scoatere a indexurilor si scaderea lor cu 1
        index2 = atoi(&conexiunea2[6]);
        index1--;
        index2--;
        if(g->madiacenta[index1][index2] == g->madiacenta[index2][index1] 
                    && g->madiacenta[index1][index2] != 0)
                fprintf(fout, "OK\n");
        else fprintf(fout, "NO\n");
}

//functia pentru rezolvarea cerintei "legatura"
void FunctiaLegatura(Graph *g, FILE *fdate, FILE *fout, char *legatura)
{
    int index1;
    fscanf(fdate, "%s", legatura);
        legatura = (char*)realloc(legatura, (strlen(legatura) + 1) * sizeof(char));
        index1 = atoi(&legatura[6]);
        index1--;
    for(int i = 0; i < g->nod; i++)
        if(g->madiacenta[index1][i] != 0) fprintf(fout,"Island%d ", i + 1);
            fprintf(fout, "\n");
}

//functia pentru rezolvarea cerintei "adauga_zbor"
void FunctiaAdaugaZbor(Graph *g, FILE *fdate, FILE *fout, char *insula1, char *insula2)
{
    int index1, index2;
        fscanf(fdate, "%s", insula1);
        insula1 = (char*)realloc(insula1, (strlen(insula1) + 1) * sizeof(char));
        fscanf(fdate, "%s", insula2);
        insula2 = (char*)realloc(insula2, (strlen(insula2) + 1) * sizeof(char));

        int cost;
        fscanf(fdate, "%d", &cost);
        index1 = atoi(&insula1[6]);
        index1--;
        index2 = atoi(&insula2[6]);
        index2--;

        g->madiacenta[index1][index2] = g->madiacenta[index2][index1] = cost;
        g->muchie += 2;
}

//functia pentru rezolvarea cerintei "anulare_zbor"
void FunctiaAnulareZbor(Graph *g, FILE *fdate, FILE *fout, char *insula1, char *insula2)
{
    int index1, index2;
    fscanf(fdate, "%s", insula1);
    insula1 = (char*)realloc(insula1, (strlen(insula1) + 1) * sizeof(char));
    fscanf(fdate, "%s", insula2);
    insula2 = (char*)realloc(insula2, (strlen(insula2) + 1) * sizeof(char));

    index1 = atoi(&insula1[6]);
    index1--;
    index2 = atoi(&insula2[6]);
    index2--;

    g->madiacenta[index1][index2] = g->madiacenta[index2][index1] = 0;
    g->muchie -= 2;   
}


//functia pentru rezolvarea cerintei "max_resurse"

void FunctiaMaxResurse(Graph *g, FILE *fdate, FILE *fout, int nr_insule, Island *ReadVec)
{
    Resursa *aux = (Resursa*)malloc(sizeof(Resursa));
    int contor = 0;
    aux->nume = (char*)malloc(1000 * sizeof(char));
    //copiaza toate rerusele, indiferent daca sunt mai multe de acelasi tip intr un vector de tip Resursa
    for(int j = 0; j < nr_insule; j++)
    for(int i = 0; i < ReadVec[j].nrResurse; i++)
        {
            aux[contor].nume = (char*)malloc(20 * sizeof(char));
            strcpy(aux[contor].nume, ReadVec[j].inventarResurse[i].nume);
            contor ++;
        }
       
    int lungime = 0;
    for(int i = 0; i < contor; i++)
        lungime += (strlen(aux[i].nume) + 1);
    aux->nume = (char*)realloc(aux->nume, (lungime + 1) * sizeof(char));
        
    int x = 0;
    //elimina dublurile din vector
    for(int i = 0; i < contor - 1; i++)
    for(int j = i + 1; j < contor; j++)
    {
        if(strcmp(aux[i].nume, aux[j].nume) == 0)
        {
            for(int k = j; k < contor - 1; k++)
            strcpy(aux[k].nume, aux[k+1].nume);
            contor--;
            j--;
        }
    }
    
    //sortare
    char *copy = (char*)malloc(20 * sizeof(char));
    for(int i = 0; i < contor - 1; i++)
    for(int j = i + 1; j < contor; j++)
        if(strcmp(aux[i].nume, aux[j].nume) > 0)
        {
            strcpy(copy, aux[i].nume);
            strcpy(aux[i].nume, aux[j].nume);
            strcpy(aux[j].nume, copy);
        }
    free(copy);
    fprintf(fout, "%d ", contor);
    for(int i = 0; i < contor; i++)
        fprintf(fout, "%s ", aux[i].nume);
    fprintf(fout, "\n");
}

//functia pentru rezolvarea cerintei "drum_zbor"
void FunctiaDrumZbor(Graph *g, FILE *fdate, FILE *fout, char *buffer)
{
    int index1, index2;

    char *insula1 = (char*)malloc(20 * sizeof(char));
    fscanf(fdate, "%s", insula1);
    insula1 = (char*)realloc(insula1, (strlen(insula1) + 1) * sizeof(char));

    char *insula2 = (char*)malloc(20 * sizeof(char));
    fscanf(fdate, "%s", insula2);
    insula2 = (char*)realloc(insula2, (strlen(insula2) + 1) * sizeof(char));

    index1 = atoi(&insula1[6]);
    index2 = atoi(&insula2[6]);
    index1--;
    index2--;

    dijkstra(g, index1, index2, fout, buffer); //apelarea dijkstra
   

}

//o functie care reprezinta un fel de "hub" al tuturor cerintelor
//verifica tipul de cerinta citit si apeleaza functia necesara / rezolva direct
void Proiectare(Graph *g, FILE *fdate, FILE *fout, Island *ReadVec, int nr_insule)
{
    int index1, index2, ok = 0;
    char *buffer = (char*)malloc(20 * sizeof(char));
    
    while(fscanf(fdate, "%s", buffer) == 1)
    {
    if(strcmp(buffer, "conexiune") == 0)
    {
        char *conexiunea1 = (char*)malloc(20 * sizeof(char));
        char *conexiunea2 = (char*)malloc(20 * sizeof(char));
        FunctiaConexiune(conexiunea1, conexiunea2, g, fdate, fout);
        
    }
    if(strcmp(buffer, "legatura") == 0)
    {
        char *legatura = (char*)malloc(20 * sizeof(char));
        FunctiaLegatura(g, fdate, fout, legatura);
    }
    if(strcmp(buffer, "adauga_zbor") == 0)
    {
        char *insula1 = (char*)malloc(20 * sizeof(char));
        char *insula2 = (char*)malloc(20 * sizeof(char));
        FunctiaAdaugaZbor(g, fdate, fout, insula1, insula2);

    }
    if(strcmp(buffer, "anulare_zbor") == 0)
    {
        char *insula1 = (char*)malloc(20 * sizeof(char));
        char *insula2 = (char*)malloc(20 * sizeof(char));
        FunctiaAnulareZbor(g, fdate, fout, insula1, insula2);
    }
    if(strcmp(buffer, "max_resurse") == 0)
    {
        FunctiaMaxResurse(g, fdate, fout, nr_insule, ReadVec);
    }
    if(strcmp(buffer, "max_cantitate") == 0)
    {
        char *resursa = (char*)malloc(20 * sizeof(char));
        fscanf(fdate, "%s", resursa);
        resursa = (char*)realloc(resursa, (strlen(resursa) + 1) * sizeof(char));
        //printf("%s\n", resursa);
        int max = 0;
        for(int i = 0; i < nr_insule; i++)
        for(int j = 0; j < ReadVec[i].nrResurse; j++)
            if(strcmp(resursa, ReadVec[i].inventarResurse[j].nume) == 0)
                if(max < ReadVec[i].inventarResurse[j].cantitate)
                    max = ReadVec[i].inventarResurse[j].cantitate;

        for(int i = 0; i < nr_insule; i++)
        for(int j = 0; j < ReadVec[i].nrResurse; j++)
            if(strcmp(resursa, ReadVec[i].inventarResurse[j].nume) == 0 && 
                    max == ReadVec[i].inventarResurse[j].cantitate)
                fprintf(fout, "%s ", ReadVec[i].nume);
        fprintf(fout,"\n");
    }
    if(strcmp(buffer, "drum_zbor") == 0)
    {
        FunctiaDrumZbor(g, fdate, fout, buffer);
        
    }
    if(strcmp(buffer, "timp_zbor") == 0)
    {
        FunctiaDrumZbor(g, fdate, fout, buffer);
    }
    if(strcmp(buffer, "min_zbor") == 0)
    {
        FunctiaDrumZbor(g, fdate, fout, buffer);
    }
    }
}



void dijkstra(Graph *g, int graphroot, int index2, FILE *fout, char *buffer)
{
    int cost[g->nod][g->nod];
    int dist[g->nod];
    int pred[g->nod];
    int sps[g->nod];
    int nr;
    int mindistance;
    int nextnode = 0;
    int i, j;

    //pentru cerintele "drum_zbor" si "timp_zbor" matricea costurilor este completata normal, pe baza matricei de adiacenta
    if(strcmp(buffer, "drum_zbor") == 0 || strcmp(buffer, "timp_zbor") == 0)
    {
       for (i = 0; i < g->nod; i++)
        for (j = 0; j < g->nod; j++)
            if (g->madiacenta[i][j] == 0)
                cost[i][j] = 777;
            else
                cost[i][j] = g->madiacenta[i][j]; 
    }
    else if(strcmp(buffer, "min_zbor") == 0) //pentru cerinta "min_zbor", unde este prevazut delay, fiecarui element != 0 in matricea de adiacenta i se adauga 15 in matricea costurilor
    {
         for (i = 0; i < g->nod; i++)
        for (j = 0; j < g->nod; j++)
            if (g->madiacenta[i][j] == 0)
                cost[i][j] = 777;
            else
                cost[i][j] = g->madiacenta[i][j] + 15; 
    }
    

    for (i = 0; i < g->nod; i++)
    {
        dist[i] = cost[graphroot][i];
        pred[i] = graphroot;
        sps[i] = 0;
    }

    dist[graphroot] = 0;
    sps[graphroot] = 1;
    nr = 1;

    while (nr < (g->nod) - 1)
    {
        mindistance = 777;

        for (i = 0; i < g->nod; i++)
            if (dist[i] < mindistance && !sps[i])
            {
                mindistance = dist[i];
                nextnode = i;   
            }
      

        sps[nextnode] = 1;
        
        for (i = 0; i < g->nod; i++)
            if (!sps[i])
                if (mindistance + cost[nextnode][i] < dist[i])
                {
                    dist[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                }
        nr++;
    }
    //dijkstra pentru "drum_zbor"
    if(strcmp(buffer, "drum_zbor") == 0)
    {
        int k = 0;
       for (i = 0; i < g->nod; i++)
        if (i != graphroot && i == index2)
        {
            
            int *v = (int*)malloc(g->nod * sizeof(int));
            if(dist[i] != 777)
            {
                v[k] = i + 1;
                k++;
            }
            else 
                fprintf(fout,"NO");
            

            j = i;
            do
            {
                j = pred[j];
                if(j != graphroot )
                {
                    v[k] = j + 1;
                    k++;      
                }
                   
            } while (j != graphroot);
        for(int j = k - 1; k >-1; k--)
            if(v[k] != 0)
            fprintf(fout, "Island%d ", v[k]);
        }
    
    fprintf(fout, "\n"); 
    
    }
    if(strcmp(buffer, "timp_zbor") == 0) //dijkstra pentru "timp_zbor"
    {

        for (i = 0; i < g->nod; i++)
        if (i != graphroot && i == index2)
        {
            if(dist[i] != 777)
            fprintf(fout,"%d\n", dist[i]);
            else fprintf(fout, "INF\n");
            j = i;
            do
            {
                j = pred[j];
            } while (j != graphroot);
        }

    }
    //dijkstra pentru "min_zbor"
    if(strcmp(buffer, "min_zbor") == 0)
    {

        for (i = 0; i < g->nod; i++)
        if (i != graphroot && i == index2)
        {
            if(dist[i] != 777)
            fprintf(fout,"%d\n", dist[i] - 15);
            else fprintf(fout, "INF\n");
            j = i;
            do
            {
                j = pred[j];
            } while (j != graphroot);
        }
    }

}


