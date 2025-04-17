#ifndef TABELAFREQUENCIA_H
#define TABELAFREQUENCIA_H

#define TAMANHO_ALFABETO 256

typedef struct {
    int frequencias[TAMANHO_ALFABETO];
} TabelaFrequencia;

TabelaFrequencia* criarTabelaFrequencia();
void gerarTabelaFrequencia(FILE* arquivo, int* frequencias);
void limparTabelaFrequencia(TabelaFrequencia* tabela);
void destruirTabela(TabelaFrequencia* tabela);

#endif
