//Structura pentru jucator:
typedef struct Player { 
   char *last_name;
   char *first_name;
   int score;
} Player;
 
//Structura pentru tara:
typedef struct Country {
   char *name;
   int nr_players;
   int global_score;
   Player *players;
} Country;

typedef struct ListaDubla {
    Country Tara;
    struct ListaDubla *next, *prev;
} ListaDubla;

typedef struct stack
{
    ListaDubla NodStiva;
    Country NodCountry;
    struct stack *urm;
}stack;
typedef struct CountriesQueue
{
    struct Country tara1;
    struct Country tara2;
}CountriesQueue;
typedef struct Q
{
    stack NodQueue;
    CountriesQueue NodCountry;
    struct Q *urmator;
    struct Q *front,*rear;
}Queue;



void ReadCountries(FILE *fdate, ListaDubla **head, int NumarEchipe);
int Stergere(ListaDubla **head, FILE *fout, int NumarEchipe);
void Printlista(ListaDubla *head, FILE *fout);
void Adaugare(ListaDubla *head, int EchipeDupaStergere, FILE *fout);
void push(stack**top, Country countryq);
Country pop(stack**top);
Queue* createQueue();
void enQueue(Queue*q, CountriesQueue countryq);
CountriesQueue deQueue(Queue*q);
int StackEmpty(stack*top);
