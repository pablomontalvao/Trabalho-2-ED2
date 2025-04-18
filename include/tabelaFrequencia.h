#ifndef TABELAFREQUENCIA_H
#define TABELAFREQUENCIA_H
#include <stdlib.h>
#include <stdio.h>
#define TAM 256

typedef struct {
    int frequencias[TAM];
} TabelaFrequencia;

TabelaFrequencia* criarTabelaFrequencia();
void gerarTabelaFrequencia(FILE* arquivo, int* frequencias);
void limparTabelaFrequencia(TabelaFrequencia* tabela);

#endif
