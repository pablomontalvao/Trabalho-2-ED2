// listaEncadeadaOrdenada.c
#include "../include/listaEncadeadaOrdenada.h"
#include <stdio.h>
#include <stdlib.h>

// Cria uma lista vazia
Lista* criarLista() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    if (lista == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a lista\n");
        exit(1);
    }
    lista->inicio = NULL;
    return lista;
}

// Verifica se a lista está vazia
int listaVazia(Lista* lista) {
    return (lista->inicio == NULL);
}

// Insere um nó na lista em ordem crescente de frequência
void inserirOrdenado(Lista* lista, No* arvore) {
    Celula* nova = (Celula*)malloc(sizeof(Celula));
    if (nova == NULL) {
        fprintf(stderr, "Erro ao alocar memória para célula\n");
        exit(1);
    }
    nova->arvore = arvore;
    nova->prox = NULL;

    if (lista->inicio == NULL || arvore->frequencia < lista->inicio->arvore->frequencia) {
        nova->prox = lista->inicio;
        lista->inicio = nova;
    } else {
        Celula* atual = lista->inicio;
        while (atual->prox != NULL && atual->prox->arvore->frequencia <= arvore->frequencia) {
            atual = atual->prox;
        }
        nova->prox = atual->prox;
        atual->prox = nova;
    }
}

// Remove e retorna a árvore do primeiro nó da lista
No* removerPrimeiro(Lista* lista) {
    if (listaVazia(lista)) return NULL;

    Celula* temp = lista->inicio;
    No* arvore = temp->arvore;
    lista->inicio = temp->prox;
    free(temp);
    return arvore;
}

// Libera todos os nós da lista
void liberarLista(Lista* lista) {
    Celula* atual = lista->inicio;
    while (atual != NULL) {
        Celula* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(lista);
}

// Constrói a árvore de Huffman a partir da lista
No* construirArvoreHuffman(Lista* lista) {
    while (lista->inicio != NULL && lista->inicio->prox != NULL) {
        No* esquerda = removerPrimeiro(lista);
        No* direita = removerPrimeiro(lista);

        int somaFreq = esquerda->frequencia + direita->frequencia;
        No* novo = criarNo('*', somaFreq, esquerda, direita);

        inserirOrdenado(lista, novo);
    }

    return removerPrimeiro(lista); // raiz da árvore
}
