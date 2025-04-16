#ifndef CODIFICACAO_HUFFMAN_H
#define CODIFICACAO_HUFFMAN_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "listaEncadeadaOrdenada.h"  // Para o tipo No*

void gerarCodigos(No *raiz, char *codigoAtual, int nivel, char* tabelaCodigos[256]) {
    if (!raiz)
        return;

    if (!raiz->esq && !raiz->dir) {
        codigoAtual[nivel] = '\0';
        tabelaCodigos[raiz->caracter] = (char *)malloc(strlen(codigoAtual) + 1);
        strcpy(tabelaCodigos[raiz->caracter], codigoAtual);
        return;
    }

    codigoAtual[nivel] = '0';
    gerarCodigos(raiz->esq, codigoAtual, nivel + 1, tabelaCodigos);

    codigoAtual[nivel] = '1';
    gerarCodigos(raiz->dir, codigoAtual, nivel + 1, tabelaCodigos);
}

#endif
