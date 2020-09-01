#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "functions.h"

void ReadCountries(FILE *fdate, ListaDubla **head, int NumarEchipe)
{
    ListaDubla *newNod = (ListaDubla*)malloc(sizeof(ListaDubla));
    if(newNod == NULL)
    {
        printf("Alocare dinamica esuata newNod!");
        exit(1);
    }
    ListaDubla *index = (ListaDubla*)malloc(sizeof(ListaDubla));
    if(index == NULL)
    {
        printf("Alocare dinamica esuata index!");
        exit(1);
    }
    ListaDubla *parcurgere = (ListaDubla*)malloc(sizeof(ListaDubla));
    if(parcurgere == NULL)
    {
        printf("Alocare dinamica esuata parcurgere!");
        exit(1);
    }

    fscanf(fdate, "%d", &newNod->Tara.nr_players);

    newNod->Tara.name = (char*)malloc(20*sizeof(char));
    fscanf(fdate,"%s" , newNod->Tara.name);
    newNod->Tara.name = (char*)realloc(newNod->Tara.name, (strlen(newNod->Tara.name)+1) * sizeof(char));

    newNod->Tara.players = (Player*)malloc(newNod->Tara.nr_players * sizeof(Player));

    for(int i = 0; i < newNod->Tara.nr_players; i++)
    {
        newNod->Tara.players[i].last_name = (char*)malloc(20 * sizeof(char));
        fscanf(fdate, "%s", newNod->Tara.players[i].last_name);

        newNod->Tara.players[i].first_name = (char*)malloc(20 * sizeof(char));
        fscanf(fdate, "%s", newNod->Tara.players[i].first_name);

        fscanf(fdate, "%d", &newNod->Tara.players[i].score);

        newNod->Tara.players[i].last_name = (char*)realloc(newNod->Tara.players[i].last_name, (strlen(newNod->Tara.players[i].last_name)+1) * sizeof(char));
        newNod->Tara.players[i].first_name = (char*)realloc(newNod->Tara.players[i].first_name, (strlen(newNod->Tara.players[i].first_name)+1) * sizeof(char));
    }
    
    (*head)->next = newNod;
    newNod->prev = (*head);
    newNod->next = index;
    (*head)->prev = index;
    index->next = (*head);
    index->prev = newNod;
    newNod = newNod->next;
   
   int nr = 0;
    for(int i = 1; i <NumarEchipe; i++)
    {
        newNod->Tara.name = (char*)malloc(20*sizeof(char));
        fscanf(fdate, "%d", &newNod->Tara.nr_players);
        fscanf(fdate,"%s" , newNod->Tara.name);
        newNod->Tara.name = (char*)realloc(newNod->Tara.name, (strlen(newNod->Tara.name)+1) * sizeof(char));
        newNod->Tara.players = (Player*)malloc(newNod->Tara.nr_players * sizeof(Player)); 
        for(int j = 0; j < newNod->Tara.nr_players; j++)
        {
            newNod->Tara.players[j].last_name = (char*)malloc(20*sizeof(char));
            fscanf(fdate, "%s", newNod->Tara.players[j].last_name);
            newNod->Tara.players[j].last_name = (char*)realloc(newNod->Tara.players[j].last_name, (strlen(newNod->Tara.players[j].last_name)+1) * sizeof(char));

            newNod->Tara.players[j].first_name = (char*)malloc(20*sizeof(char));
            fscanf(fdate, "%s", newNod->Tara.players[j].first_name);
            newNod->Tara.players[j].first_name = (char*)realloc(newNod->Tara.players[j].first_name, (strlen(newNod->Tara.players[j].first_name)+1) * sizeof(char));

            fscanf(fdate, "%d", &newNod->Tara.players[j].score);
        }
        ListaDubla *parcurgere = (ListaDubla*)malloc(sizeof(ListaDubla));
        parcurgere->next = *head;
        parcurgere->prev = newNod;
        newNod->next = parcurgere;
        newNod = newNod->next;
    }

}

void Printlista(ListaDubla *head, FILE *fout)
{
    ListaDubla *headcopy;
    headcopy = head;
    if(headcopy == NULL)
    {
        printf("Alocare dinamica esuata headcopy!");
        exit(1);
    }
    headcopy = headcopy->next;

    while(headcopy->next != head)
    {
        fprintf(fout, "%s\n", headcopy->Tara.name);
        headcopy = headcopy->next;
    } 
}

int Stergere(ListaDubla **head, FILE *fout, int NumarEchipe)
{
    int putere = 2; //2^1
    float medie = 0;
    while(putere * 2 < NumarEchipe)
        putere = putere * 2;
    float *VectorScor = (float*)malloc(NumarEchipe * sizeof(float));

    ListaDubla *parcurgere = (ListaDubla*)malloc(sizeof(ListaDubla));
    parcurgere = *head;
    parcurgere = parcurgere->next;

    for(int i = 0; i < NumarEchipe; i++)
    {
        for(int j = 0; j < parcurgere->Tara.nr_players; j++)
            medie = medie + parcurgere->Tara.players[j].score;
        medie = medie / parcurgere->Tara.nr_players;
        VectorScor[i] = medie;
        medie = 0;
        parcurgere = parcurgere->next;
    }

    int EchipeCopy = NumarEchipe;
    int j = 0;
    while(putere < EchipeCopy)
    {
        parcurgere = *head;
        parcurgere = parcurgere->next;

        float minim = VectorScor[0];
        for(int i = 1; i < EchipeCopy; i++)
            if(minim > VectorScor[i]) minim = VectorScor[i];

        j = 0;
        while(minim != VectorScor[j])
        {
            parcurgere = parcurgere->next;
            j++;
        }

        ListaDubla *legatura = (ListaDubla*)malloc(sizeof(ListaDubla));
          if(legatura == NULL)
        {
            printf("Eroare alocare dinamica legatura in functia Stergere!");
            exit(1);
        }

        if(parcurgere->prev == (*head))
        {
            legatura = parcurgere->next;
            (*head)->next = legatura;
            legatura->prev = (*head);
            free(parcurgere);
        }
        else if(parcurgere->next == (*head))
        {
            legatura = parcurgere->prev;
            legatura->next = (*head);
            (*head)->prev = legatura;
            free(parcurgere);
        }
        else
        {
            legatura = parcurgere->prev;
            parcurgere->prev->next = parcurgere->next;
            parcurgere->next->prev = legatura;
            free(parcurgere); 
        }

        for(int i = 0; i < EchipeCopy-1; i++)
            if(minim == VectorScor[i])
            {
                for(int j = i; j < EchipeCopy-1; j++)
                    VectorScor[j] = VectorScor[j+1];
                EchipeCopy--;
                break;
            }  
        if(minim == VectorScor[EchipeCopy-1]) EchipeCopy--;
    }   
    return EchipeCopy;
}

Queue* createQueue()  //crearea cozii
{
Queue *q;
q=(Queue *)malloc(sizeof(Queue));
if (q==NULL) return NULL;
q->front=q->rear=NULL;
return q;
}

void push(stack**top, Country countryq) //varful trebuie intors modificat din functie
{
    stack* newNode = (stack*)malloc(sizeof(stack));
    newNode->NodCountry = countryq;
    newNode->urm = (*top);
    *top = newNode;
}


Country pop(stack**top) // se returneaza informatia stocata in varf si se stege acest nod
{
    stack *temp = (*top); //stochez adresa varful in temp
    Country aux = (temp)->NodCountry;

    *top=(*top)->urm; //sterg elementul din varf
    free(temp);
    return aux;
}

int StackEmpty(stack*top){
return top==NULL;
} 

void enQueue(Queue*q, CountriesQueue countryq)  //adaugare in coada
{
    Queue* newNode=(Queue*)malloc(sizeof(Queue));
    newNode->NodCountry = countryq;
    newNode->urmator = NULL;
    if (q->rear == NULL) q->rear = newNode;
    else
    {
        (q->rear)->urmator = newNode;
        (q->rear) = newNode;
    }
    if (q->front == NULL) q->front = q->rear; 
}

int isEmpty(Queue*q){
return (q->front==NULL);
}

CountriesQueue deQueue(Queue*q) 
{
Queue *aux;
CountriesQueue countryq;
if (isEmpty(q)) 
    printf("%d", INT_MIN);
aux =q->front;
//printf("%s %s\n", q->front->NodCountry.tara1.name, q->front->NodCountry.tara2.name);
countryq = aux->NodCountry;
q->front=(q->front)->urmator;
free(aux);
return countryq;
}


void Adaugare(ListaDubla *head, int EchipeDupaStergere, FILE *fout)
{
    Queue *q;
    q = createQueue();
    stack *top = NULL;
    stack *topwinner = NULL;
    CountriesQueue countryq;
    CountriesQueue castigator;
    ListaDubla *parcurgere;
    int runda = 1;
    parcurgere = head->next;
    while(parcurgere->next != head)
    {   
        push(&top, parcurgere->Tara);
        parcurgere = parcurgere->next;
    }
    
    /*while (EchipeDupaStergere != 1)
    {*/
    for (int i = 0; i < EchipeDupaStergere; i = i + 2)
        {
            countryq.tara1 = pop(&top);
            countryq.tara2 = pop(&top);
            enQueue(q, countryq);
        }

    fprintf(fout, "\n====== ETAPA %d ======\n", runda);
    
    for(int i = 0; i < EchipeDupaStergere; i = i + 2)
    {
        int ScorLocal1 = 0, ScorLocal2 = 0;    
        countryq = deQueue(q);
        fprintf(fout, "\n%s %d ----- %s %d\n", countryq.tara1.name, countryq.tara1.global_score, countryq.tara2.name, countryq.tara1.global_score);
       for (int j = 0; j < countryq.tara1.nr_players; j++)
       for (int k = 0; k < countryq.tara2.nr_players; k++)
       {
            fprintf(fout, "%s %s %d ", countryq.tara1.players[j].last_name, countryq.tara1.players[j].first_name, countryq.tara1.players[j].score);
            fprintf(fout,"vs %s %s %d\n", countryq.tara2.players[k].last_name, countryq.tara2.players[k].first_name, countryq.tara2.players[k].score);
            if (countryq.tara1.players[j].score > countryq.tara2.players[k].score)
                    {
                        ScorLocal1 += 3;
                        countryq.tara1.players[j].score += 5;
                    }
                    else if (countryq.tara1.players[j].score < countryq.tara2.players[k].score)
                    {
                        ScorLocal2 += 3;
                        countryq.tara2.players[k].score += 5;
                    }
                    else
                    {
                        ScorLocal1 += 1;
                        ScorLocal2 += 1;
                        countryq.tara1.players[j].score += 2;
                        countryq.tara2.players[k].score += 2;
                    }
       }
       countryq.tara1.global_score += ScorLocal1;
       countryq.tara2.global_score += ScorLocal2;
       if(ScorLocal1 > ScorLocal2)
            push(&topwinner, countryq.tara1);
        else if(ScorLocal1 < ScorLocal2)
            push(&topwinner, countryq.tara2);
        else if(ScorLocal1 == ScorLocal2)
        {
            int maxim1 = 0, maxim2 = 0;
            for(int i = 0; i < countryq.tara1.nr_players; i++)
                if(maxim1 < countryq.tara1.players[i].score) maxim1 = countryq.tara1.players[i].score;
            for(int i = 0; i < countryq.tara2.nr_players; i++)
                if(maxim2 < countryq.tara2.players[i].score) maxim2 = countryq.tara2.players[i].score;
            if(maxim1 > maxim2)
                push(&topwinner, countryq.tara1);
            else if(maxim1 < maxim2)
                push(&topwinner, countryq.tara2);
        }
    }
        fprintf(fout, "\n=== WINNER ===\n");
        EchipeDupaStergere = EchipeDupaStergere / 2;
        for (int i = 0; i < EchipeDupaStergere; i++)
        {
            castigator.tara1 = pop(&topwinner);
            push(&top, castigator.tara1);
            fprintf(fout, "%s --- %d\n", castigator.tara1.name, castigator.tara1.global_score);
        }
        runda++;
        printf("%d", EchipeDupaStergere);
    //}
        
}