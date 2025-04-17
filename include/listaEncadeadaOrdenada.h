// listaEncadeadaOrdenada.h
#ifndef LISTA_ENCADEADA_ORDENADA_H
#define LISTA_ENCADEADA_ORDENADA_H

#include "arvoreBin.h"

// Estrutura de um nó da lista encadeada
typedef struct Celula {
    No* arvore;
    struct Celula* prox;
} Celula;

// Estrutura da lista
typedef struct Lista {
    Celula* inicio;
} Lista;

// Cria uma nova lista vazia
Lista* criarLista();

// Insere um nó na lista de forma ordenada pela frequência
void inserirOrdenado(Lista* lista, No* arvore);

// Remove e retorna o primeiro nó da lista
No* removerPrimeiro(Lista* lista);

// Verifica se a lista está vazia
int listaVazia(Lista* lista);

// Libera a lista encadeada
void liberarLista(Lista* lista);

// Constrói a árvore de Huffman a partir da lista ordenada
No* construirArvoreHuffman(Lista* lista);

#endif
