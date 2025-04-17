#ifndef ARVOREBIN_H
#define ARVOREBIN_H

#include <stdio.h>

typedef struct No {
    unsigned char caractere;
    int frequencia;
    struct No* esq;
    struct No* dir;
} No;

No* criarNo(unsigned char caractere, int frequencia, No* esq, No* dir);
int ehFolha(No* no);
void gerarCodigos(No* raiz, char** tabela, char* codigo, int profundidade);
void escreverArvoreHuffman(No* raiz, FILE* arquivo);
No* lerArvoreHuffman(FILE* arquivo);
void liberarArvore(No* raiz);

#endif
