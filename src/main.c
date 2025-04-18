#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/arvoreHuff.h"
#include "../include/tabelaFrequencia.h"
#include "../include/manipulacaoArquivos.h"

void interfaceUsuario(){
    printf("\n\n============================================\n");
    printf("\n== Compressao e descompressao de arquivos ==\n");
    printf("\n(1) - Compactar");
    printf("\n(2) - Descompactar");
    printf("\n(3) - Comparacao arquivo original e compactado");
    printf("\n(0) - Sair do programa");
    printf("\n");
    printf("\n============================================\n\n");
}

int main() {
    
    int opcao;
    char entrada[100], saida[100];

    do {
        interfaceUsuario();
        scanf("%d",&opcao);

        switch(opcao){
        case 1:
            printf("\nDigite o nome ou path do arquivo a ser compactado: ");
            scanf("%s", entrada);

            printf("Digite o nome ou path do arquivo compactado de saida: ");
            scanf("%s", saida);
            compactarArquivo(entrada, saida);
            break;

        case 2:
            printf("Digite o nome ou path do arquivo compactado: ");
            scanf("%s", entrada);

            printf("Digite o nome ou path do arquivo descompactado de saida: ");
            scanf("%s", saida);
            descompactarArquivo(entrada, saida);
            break;

        case 3:
            if(getTamanhoArquivo(entrada) == -1 || getTamanhoArquivo(saida) == -1){
                printf("\nNenhum arquivo foi compactado ainda. Repita a etapa 1 e compacte seu arquivo.\n");
                break;
            }

            printf("\nTamanho do arquivo original: %ld bytes", getTamanhoArquivo(entrada));
            printf("\nTamanho arquivo compactado: %ld bytes", getTamanhoArquivo(saida));
            break;

        case 0:
            printf("\nSaindo do programa...");
            break;

        default:
            printf("\nOpcao invalida, digite um numero valido. ");
        }
    } while(opcao != 0);
    
    return 0;
}
