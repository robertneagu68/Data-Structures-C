//Structura pentru resurse:

typedef struct Resursa 
{
    char *nume;
    int cantitate;
}Resursa;

//Structura pentru insula:

typedef struct Island
{
    char *nume;
    int nrResurse;
    Resursa *inventarResurse;
    int nrAvioane;
    int *avioane;
    int tolAvioane;
}Island;

//Structura pentru graf:

typedef struct Graf
{
    int nod;
    int muchie;
    int **madiacenta;
    //Island *ReadVec;
}Graph;

//Functiile necesare in rezolvarea cerintelor
Island* Read(int nr_insule, FILE *fdate, Island *ReadVec);
Graph * create (int nr_conexiuni, FILE *fdate, Graph *g, int nr_insule);
void printGraph(Graph *g);
void Proiectare(Graph *g, FILE *fdate, FILE *fout, Island *ReadVec, int nr_insule);
void FunctiaConexiune(char *conexiunea1, char *conexiunea2, Graph *g, FILE *fdate, FILE *fout);
void FunctiaLegatura(Graph *g, FILE *fdate, FILE *fout, char *legatura);
void FunctiaAdaugaZbor(Graph *g, FILE *fdate, FILE *fout, char *insula1, char *insula2);
void FunctiaAnulareZbor(Graph *g, FILE *fdate, FILE *fout, char *insula1, char *insula2);
void FunctiaMaxResurse(Graph *g, FILE *fdate, FILE *fout, int nr_insule, Island *ReadVec);
void FunctiaDrumZbor(Graph *g, FILE *fdate, FILE *fout, char *buffer);
void dijkstra(Graph *g, int graphroot, int index2, FILE *fout, char *buffer);

