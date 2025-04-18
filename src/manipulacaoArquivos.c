#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include "../include/arvoreHuff.h"
#include "../include/manipulacaoArquivos.h"

// funcao de compactacao
int compactarArquivo(const char* nomeEntrada, const char* nomeSaida) {
    setlocale(LC_ALL, "Portuguese");
    // abrindo arquivo, com base no nome passado pelo usuario
    FILE* entrada = fopen(nomeEntrada, "rb");
    if (!entrada) {
        printf("Erro ao abrir arquivo de entrada. Tente passar o caminho do seu texto (ex: ../data/livroseflores.txt)\n");
        return 0;
    }

    int freq[TAM] = {0};
    gerarTabelaFrequencia(entrada, freq);

    No* raiz = construirArvore(freq);

    char* tabelaCodigos[TAM] = {NULL};
    char codigo[256];
    gerarCodigos(raiz, tabelaCodigos, codigo, 0);

    FILE* saida = fopen(nomeSaida, "wb");
    if (!saida) {
        printf("Erro ao criar arquivo de saida.\n");
        return 0;
    }

    escreverArvoreHuffman(raiz, saida);
    fputc('#', saida); // marcando o fim da árvore

    unsigned char c;
    unsigned char buffer = 0;
    int bits = 0;

    // lendo arquivo byte a byte, adicionando cada bit ao buffer incluindo o deslocamento dos bits.
    while (fread(&c, 1, 1, entrada) == 1) {
        char* cod = tabelaCodigos[c];
        for (int i = 0; cod[i] != '\0'; i++) {
            buffer <<= 1;
            if (cod[i] == '1') buffer |= 1;
            bits++;

            if (bits == 8) {
                fwrite(&buffer, 1, 1, saida);
                bits = 0;
                buffer = 0;
            }
        }
    }
    // gravando no arquivo de saida a cada byte lido (8 bits).
    if (bits > 0) {
        buffer <<= (8 - bits);
        fwrite(&buffer, 1, 1, saida);
    }

    // fechando e liberando memoria
    fclose(entrada);
    fclose(saida);
    liberarArvore(raiz);
    printf("Arquivo compactado com sucesso!\n");
    return 1;
}

//funcao de descompactacao, lendo a arvore de huffman do arquivo
int descompactarArquivo(const char* nomeCompactado, const char* nomeSaida) {
    setlocale(LC_ALL, "Portuguese");
    // lendo o arquivo compactado
    FILE* entrada = fopen(nomeCompactado, "rb");
    if (!entrada) {
        printf("Erro ao abrir arquivo compactado. Verifique se o nome ou caminho do arquivo foi passado corretamente ou, repita a etapa 1 e compacte seu arquivo.\n");
        return 0;
    }

    // leitura da arvore
    No* raiz = lerArvoreHuffman(entrada);
    int c;
    while ((c = fgetc(entrada)) != '#' && c != EOF); // pula marcador

    FILE* saida = fopen(nomeSaida, "wb");
    if (!saida) {
        printf("Erro ao criar arquivo descompactado.\n");
        return 0;
    }

    No* atual = raiz;
    unsigned char byte;

    // lendo o arquivo byte a byte, decodificando de acordo com o valor de cada bit(0 ou 1)
    while (fread(&byte, 1, 1, entrada) == 1) {
        for (int i = 7; i >= 0; i--) {
            int bit = (byte >> i) & 1;
            atual = bit == 0 ? atual->esq : atual->dir;

            if (ehFolha(atual)) {
                fwrite(&atual->caractere, 1, 1, saida);
                atual = raiz;
            }
        }
    }

    //fechamento e liberaçao de memoria
    fclose(entrada);
    fclose(saida);
    liberarArvore(raiz);
    printf("Arquivo descompactado com sucesso!\n");
    return 1;
}

//funcao que retorna o tamanho do arquivo 
long int getTamanhoArquivo(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "rb");
    if (!arquivo) {
        return -1;
    }

    // move o ponteiro para o final do arquivo
    fseek(arquivo, 0, SEEK_END); 
    // tamanho do arquivo, obtido através da posicao do ponteiro (final do arquivo).
    long int tamanho = ftell(arquivo); 
    fclose(arquivo);

    return tamanho;
}