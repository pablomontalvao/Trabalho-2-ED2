#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreBin.h"

No* criarNo(unsigned char caractere, int frequencia, No* esq, No* dir) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->caractere = caractere;
    novoNo->frequencia = frequencia;
    novoNo->esq = esq;
    novoNo->dir = dir;
    return novoNo;
}

int ehFolha(No* no) {
    return (no->esq == NULL && no->dir == NULL);
}

void gerarCodigos(No* raiz, char** tabela, char* codigo, int profundidade) {
    if (raiz == NULL) return;

    if (ehFolha(raiz)) {
        codigo[profundidade] = '\0';
        tabela[raiz->caractere] = strdup(codigo);
    }

    codigo[profundidade] = '0';
    gerarCodigos(raiz->esq, tabela, codigo, profundidade + 1);

    codigo[profundidade] = '1';
    gerarCodigos(raiz->dir, tabela, codigo, profundidade + 1);
}

void escreverArvoreHuffman(No* raiz, FILE* arquivo) {
    if (raiz == NULL) return;

    if (ehFolha(raiz)) {
        fputc('1', arquivo);
        fputc(raiz->caractere, arquivo);
    } else {
        fputc('0', arquivo);
        escreverArvoreHuffman(raiz->esq, arquivo);
        escreverArvoreHuffman(raiz->dir, arquivo);
    }
}

No* lerArvoreHuffman(FILE* arquivo) {
    int c = fgetc(arquivo);
    if (c == '1') {
        unsigned char caractere = fgetc(arquivo);
        return criarNo(caractere, 0, NULL, NULL);
    } else if (c == '0') {
        No* esq = lerArvoreHuffman(arquivo);
        No* dir = lerArvoreHuffman(arquivo);
        return criarNo(0, 0, esq, dir);
    }
    return NULL;
}

void liberarArvore(No* raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}
