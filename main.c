#include <stdio.h>
#include <stdlib.h>
#include "arvoreBin.h"
#define TAM 256 //tamanho tabela ASCII

/*
Definindo etapas: 
1- Ler o txt e gerar tabela de frequencia de letras (hash table)
2- gerar fila com os nós da árvore, ordenada por frequência (nó -> caracter, frequencia, esq, dir, prox)
3- gerar a árvore de huffman 
4- gerar tabela de codificação (matriz de string)
5- codificar o texto
6- decodificar o texto
7- comparar os arquivos original e compactado
*/

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



int main()
{
    int opcao;
    unsigned char texto = "texto a ser compactado"; //será substituido por um arquivo lido
    unsigned int frequenceTable [TAM];
    do {
        interfaceUsuario();
        scanf("%d",&opcao);

        switch(opcao){

        case 1:
            printf("\nDigite o nome do arquivo a ser compactado: ");
            //...


            break;

        case 2:
            printf("\nDigite o nome do arquivo a ser descompactado: ");
            //...

            break;

        case 3:
            printf("\nArquivo original: ");
            //ler arquivo original

            printf("\nArquivo compactado: ");
            //ler arquivo compactado

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
