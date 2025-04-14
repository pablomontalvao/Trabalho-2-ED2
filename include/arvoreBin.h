#include <stdio.h>
#include <stdlib.h>



ArvBin* cria_ArvBin();
void libera_ArvBin(ArvBin *raiz);
int insere_ArvBin(ArvBin* raiz, int valor);
int remove_ArvBin(ArvBin *raiz, int valor);
int estaVazia_ArvBin(ArvBin *raiz);
int altura_ArvBin(ArvBin *raiz);
int totalNO_ArvBin(ArvBin *raiz);
int consulta_ArvBin(ArvBin *raiz, int valor);
void preOrdem_ArvBin(ArvBin *raiz);
void emOrdem_ArvBin(ArvBin *raiz);
void posOrdem_ArvBin(ArvBin *raiz);

typedef struct no{
	unsigned char caracter;
	int freq;
	struct no *esq, *dir, *prox;
}No;

typedef struct lista{
    No *inicio;
    int tam;
}Lista;

No* ArvBin;


void criaLista(Lista *li){
    li->inicio = NULL;
    li->tam = 0;
}

void insereOrdenado(Lista *li, No *no){
    No *aux;
    //se a lista esta vazia
    if(li->inicio == NULL){
        li->inicio = no;
    }
    //tem freq menor que o inicio
    else if(no->freq < li->inicio->freq){
        no->prox = li->inicio;
        li->inicio = no;
    }
    else{
        aux = li->inicio;
        while(aux->proximo && aux->prox->freq <= no->freq)
            aux = aux->prox;
        no->prox = aux->prox;
        aux->prox = no;
    }

    li->tam++;
}

void preencheLista(unsigned int tab[], Lista *li){
    No *newNo;
    for(int i = 0; i < TAM; i++){
        if(tab[i] > 0){
            newNo = malloc(sizeof(No));
            if(newNo){
                newNo->caracter = i;
                newNo->freq = tab[i];
                newNo->dir = NULL;
                newNo->esq = NULL;
                newNo->prox = NULL;

                insereOrdenado(li, newNo);
            }
            else{
                printf("\nErro no preenchimento da lista\n");
                break;
            }
        }
    }

void imprimeLista(Lista *li){
    No *aux = li->inicio;

    printf("\nTamanho lista:%d \n", li->tam);
    while(aux){
        printf("\nCaracter: %c Frequencia:%d", aux->caracter, aux->freq);
        aux = aux->prox;
    }


}
ArvBin* cria_ArvBin(){
	ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
	if(raiz != NULL)
		*raiz = NULL;
	return raiz;
}

void libera_NO(struct no* no){
	if(no == NULL)
		return;
	libera_NO(no->esq);
	libera_NO(no->dir);
	free(no);
	no = NULL;
}

void libera_ArvBin(ArvBin* raiz){
	if(raiz == NULL)
		return;
	libera_NO(*raiz); // libera cada n�
	free(raiz); // libera a raiz
}

int estaVazia_ArvBin(ArvBin *raiz){
	if(raiz == NULL)
		return 1;
	if(*raiz == NULL)
		return 1;
	return 0;
}

int totalNO_ArvBin(ArvBin *raiz){
	if (raiz == NULL)
		return 0;
	if (*raiz == NULL)
		return 0;
	int totalNO_esq = totalNO_ArvBin(&((*raiz)->esq));
	int totalNO_dir = totalNO_ArvBin(&((*raiz)->dir));
	return (totalNO_esq + totalNO_dir + 1);
}

int altura_ArvBin(ArvBin *raiz){
	if (raiz == NULL)
		return 0;
	if (*raiz == NULL)
		return 0;
	int alt_esq = altura_ArvBin(&((*raiz)->esq));
	int alt_dir = altura_ArvBin(&((*raiz)->dir));
	if (alt_esq > alt_dir)
		return (alt_esq + 1);
	else
		return(alt_dir + 1);
}

int insere_ArvBin(ArvBin* raiz, int valor){
	if(raiz == NULL)
		return 0;
	struct NO* novo;
	novo = (struct NO*) malloc(sizeof(struct NO));
	if(novo == NULL)
		return 0;
	novo->info = valor;
	novo->dir = NULL;
	novo->esq = NULL;

	if(*raiz == NULL)
		*raiz = novo;
	else{
		struct NO* atual = *raiz;
		struct NO* ant = NULL;

		// Navega nos n�s da �rvore at� chegar em um n� folha
		while(atual != NULL){
			ant = atual;
			if(valor == atual->info){
				free(novo);
				return 0; // elemento j� existe
			}

			if(valor > atual->info)
				atual = atual->dir;
			else
				atual = atual->esq;
		}

		// Insere como filho desse n� folha
		if(valor > ant->info)
			ant->dir = novo;
		else
			ant->esq = novo;
	}
	return 1;
}

int consulta_ArvBin(ArvBin *raiz, int valor){
	if (raiz == NULL)
		return 0;
	struct NO* atual = *raiz;
	while (atual != NULL){
		if (valor == atual->info){
			return 1;
		}
		if (valor > atual->info)
			atual = atual->dir;
		else
			atual = atual->esq;
	}
	return 0;
}



