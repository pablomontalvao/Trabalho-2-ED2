#define TAM 256

// Definição da estrutura No
typedef struct no {
    unsigned char caracter;
    int freq;
    struct no *esq, *dir, *prox;
} No;

// Definição da estrutura Lista
typedef struct lista {
    No *inicio;
    int tam;
} Lista;

void criaLista(Lista *li);
void insereOrdenado(Lista *li, No *no);
void preencheLista(unsigned int tab[], Lista *li);
void imprimeLista(Lista *li);

