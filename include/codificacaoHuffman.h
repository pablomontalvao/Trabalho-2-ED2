#include <string.h>
#include <stdlib.h>

void gerarCodigos(No *raiz, char *codigoAtual, int nivel, char* tabelaCodigos[256]) {
    if (!raiz)
        return;

    // Verifica se é folha
    if (!raiz->esq && !raiz->dir) {
        codigoAtual[nivel] = '\0';  // Finaliza a string
        tabelaCodigos[raiz->caracter] = (char *)malloc(strlen(codigoAtual) + 1);
        strcpy(tabelaCodigos[raiz->caracter], codigoAtual);
        return;
    }

    // Vai para a esquerda (bit 0)
    codigoAtual[nivel] = '0';
    gerarCodigos(raiz->esq, codigoAtual, nivel + 1, tabelaCodigos);

    // Vai para a direita (bit 1)
    codigoAtual[nivel] = '1';
    gerarCodigos(raiz->dir, codigoAtual, nivel + 1, tabelaCodigos);
}
