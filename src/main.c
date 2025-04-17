#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreBin.h"
#include "tabelaFrequencia.h"

#define TAM 256

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

void compactarArquivo(const char* nomeEntrada, const char* nomeSaida) {
    FILE* entrada = fopen(nomeEntrada, "rb");
    if (!entrada) {
        printf("Erro ao abrir arquivo de entrada.\n");
        return;
    }

    int freq[TAM] = {0};
    gerarTabelaFrequencia(entrada, freq);

    No* raiz = construirArvore(freq);

    char* tabelaCodigos[TAM] = {NULL};
    char codigo[256];
    gerarCodigos(raiz, tabelaCodigos, codigo, 0);

    FILE* saida = fopen(nomeSaida, "wb");
    if (!saida) {
        printf("Erro ao criar arquivo de saída.\n");
        return;
    }

    escreverArvoreHuffman(raiz, saida);
    fputc('#', saida); // marcador de fim da árvore

    unsigned char c;
    unsigned char buffer = 0;
    int bits = 0;

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

    if (bits > 0) {
        buffer <<= (8 - bits);
        fwrite(&buffer, 1, 1, saida);
    }

    fclose(entrada);
    fclose(saida);
    liberarArvore(raiz);
    printf("Arquivo compactado com sucesso!\n");
}

void descompactarArquivo(const char* nomeCompactado, const char* nomeSaida) {
    FILE* entrada = fopen(nomeCompactado, "rb");
    if (!entrada) {
        printf("Erro ao abrir arquivo compactado.\n");
        return;
    }

    No* raiz = lerArvoreHuffman(entrada);
    int c;
    while ((c = fgetc(entrada)) != '#' && c != EOF); // pula marcador

    FILE* saida = fopen(nomeSaida, "wb");
    if (!saida) {
        printf("Erro ao criar arquivo descompactado.\n");
        return;
    }

    No* atual = raiz;
    unsigned char byte;
    int totalBits;

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

    fclose(entrada);
    fclose(saida);
    liberarArvore(raiz);
    printf("Arquivo descompactado com sucesso!\n");
}

int main() {
    int opcao;
    char entrada[100], saida[100];

    do {
        printf("\n=== Compactador Huffman ===\n");
        printf("1. Compactar arquivo\n");
        printf("2. Descompactar arquivo\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("Digite o nome do arquivo a ser compactado: ");
            scanf("%s", entrada);
            printf("Digite o nome do arquivo compactado de saída: ");
            scanf("%s", saida);
            compactarArquivo(entrada, saida);
        } else if (opcao == 2) {
            printf("Digite o nome do arquivo compactado: ");
            scanf("%s", entrada);
            printf("Digite o nome do arquivo descompactado de saída: ");
            scanf("%s", saida);
            descompactarArquivo(entrada, saida);
        }

    } while (opcao != 0);

    return 0;
}
