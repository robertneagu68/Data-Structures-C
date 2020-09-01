#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(int argc, char const *argv[])
{
    FILE *fcerinte = fopen(argv[1], "rt");
    if(fcerinte == NULL)
    {
        printf("Eroare deschidere fisier cerinte.in !");
        exit(1);
    }

    FILE *fdate = fopen(argv[2], "rt");
    if(fdate == NULL)
    {
        printf("Eroare deschidere fisier date.in !");
        exit(1);
    }

    FILE *fout = fopen(argv[3], "wt");
    if(fout == NULL)
    {
        printf("Eroare deschidere fisier date.out !");
        exit(1);
    }

    int n, *cerinte;
    n = 5; //numarul cerintelor;

    //In situatia de fata head este santinela
    ListaDubla *head = (ListaDubla*)malloc(sizeof(ListaDubla));

    int NumarEchipe = 0;
    fscanf(fdate, "%d", &NumarEchipe);

    stack *top = NULL;
    stack *topwinner = NULL;
    Queue *q;
    q = createQueue();


        /*if(cerinte[0] == 1 && cerinte[1] == 0 && cerinte[2] == 0 && cerinte[3] == 0 && cerinte[4] == 0)
        {
            ReadCountries(fdate, &head, NumarEchipe);
            Printlista(head, fout);
        }
        else if(cerinte[0] == 1 && cerinte[1] == 1 && cerinte[2] == 0 && cerinte[3] == 0 && cerinte[4] == 0)
        {
           int EchipeDupaStergere;
           ReadCountries(fdate, &head, NumarEchipe);
           EchipeDupaStergere = Stergere(&head, fout, NumarEchipe);
           Printlista(head, fout);
        }
        else if(cerinte[0] == 1 && cerinte[1] == 1 && cerinte[2] == 1 && cerinte[3] == 0 && cerinte[4] == 0)
        {
            int EchipeDupaStergere;
            ReadCountries(fdate, &head, NumarEchipe);
            EchipeDupaStergere = Stergere(&head, fout, NumarEchipe);
            Adaugare(head, EchipeDupaStergere, fout);
    
        }*/
         int EchipeDupaStergere;
            ReadCountries(fdate, &head, NumarEchipe);
            EchipeDupaStergere = Stergere(&head, fout, NumarEchipe);
            Adaugare(head, EchipeDupaStergere, fout);
   
}