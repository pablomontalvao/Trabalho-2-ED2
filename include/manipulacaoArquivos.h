#ifndef MANIPULACAO_ARQUIVOS_H
#define MANIPULACAO_ARQUIVOS_H

#include "arvoreHuff.h"

int compactarArquivo(const char* nomeEntrada, const char* nomeSaida);
int descompactarArquivo(const char* nomeCompactado, const char* nomeSaida);
long int getTamanhoArquivo(const char* nomeArquivo);

#endif