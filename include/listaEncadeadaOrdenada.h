#include <stdlib.h>
#include <stdio.h>
#define TAM 256

/*
criar_lista(&lista);
preenche_lista(tabelaFrequencia, &lista);
imprime_lista(&lista);
*/

// estrutura do nó da lista encadeada
typedef struct no{
	unsigned char caracter;
	int freq;
	struct no *esq, *dir, *prox;
}No;

// estrutura da lista encadeada
typedef struct lista{
    No *inicio;
    int tam;
}Lista;

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
        while(aux->prox && aux->prox->freq <= no->freq)
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
            newNo = (No*)malloc(sizeof(No));
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
}

void imprimeLista(Lista *li){
    No *aux = li->inicio;

    printf("\nTamanho lista:%d \n", li->tam);
    while(aux){
        printf("\nCaracter: %c Frequencia:%d", aux->caracter, aux->freq);
        aux = aux->prox;
    }
}

No* construirArvoreHuffman(Lista *li) {
    while (li->tam > 1) {
        // Remove os dois primeiros nós de menor frequência
        No *esq = li->inicio;
        No *dir = esq->prox;

        // Remove da lista
        li->inicio = dir->prox;
        li->tam -= 2;

        // Cria novo nó combinando os dois
        No *novo = (No *)malloc(sizeof(No));
        if (!novo) {
            printf("Erro ao alocar nó da árvore de Huffman.\n");
            return NULL;
        }

        novo->caracter = '*'; // caractere genérico para nós internos
        novo->freq = esq->freq + dir->freq;
        novo->esq = esq;
        novo->dir = dir;
        novo->prox = NULL;

        // Insere novamente na lista de forma ordenada
        insereOrdenado(li, novo);
    }

    // No final, o único nó restante é a raiz da árvore
    return li->inicio;
}
