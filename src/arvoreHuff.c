#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/arvoreHuff.h"

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

No* construirArvore(int* freq) {
    No* lista[TAM] = {NULL};
    int n = 0;

    for (int i = 0; i < TAM; i++) {
        if (freq[i] > 0) {
            lista[n++] = criarNo((unsigned char)i, freq[i], NULL, NULL);
        }
    }

    while (n > 1) {
        int menor1 = 0, menor2 = 1;
        if (lista[menor2]->frequencia < lista[menor1]->frequencia) {
            int tmp = menor1;
            menor1 = menor2;
            menor2 = tmp;
        }

        for (int i = 2; i < n; i++) {
            if (lista[i]->frequencia < lista[menor1]->frequencia) {
                menor2 = menor1;
                menor1 = i;
            } else if (lista[i]->frequencia < lista[menor2]->frequencia) {
                menor2 = i;
            }
        }

        No* novo = criarNo(0, lista[menor1]->frequencia + lista[menor2]->frequencia, lista[menor1], lista[menor2]);

        lista[menor1] = novo;
        for (int i = menor2; i < n - 1; i++) {
            lista[i] = lista[i + 1];
        }
        n--;
    }

    return lista[0];
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
