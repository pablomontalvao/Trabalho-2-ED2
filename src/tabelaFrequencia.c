#include <stdio.h>
#include <stdlib.h>
#include "../include/tabelaFrequencia.h"

TabelaFrequencia* criarTabelaFrequencia() {
    TabelaFrequencia* tabela = (TabelaFrequencia*)malloc(sizeof(TabelaFrequencia));
    limparTabelaFrequencia(tabela);
    return tabela;
}

void gerarTabelaFrequencia(FILE* arquivo, int* frequencias) {
    unsigned char c;
    while (fread(&c, 1, 1, arquivo) == 1) {
        frequencias[c]++;
    }
    rewind(arquivo);
}

void limparTabelaFrequencia(TabelaFrequencia* tabela) {
    for (int i = 0; i < TAM; i++) {
        tabela->frequencias[i] = 0;
    }
}
