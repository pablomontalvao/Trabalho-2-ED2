#include <stdlib.h>
#include <stdio.h>
#include "../include/tabelaFrequencia.h"

void inicializaTabelaFrequencia(unsigned int tabelaFrequencia[]){
    for(int i = 0; i < TAM; i++){
        tabelaFrequencia[i] = 0;
    }
}

void preencheTabelaFrequencia(unsigned char texto[], unsigned int tabelaFrequencia[]){
    int i = 0;
    //preenche a tabela com a frequencia de cada letra
    while(texto[i] != '\0'){
        tabelaFrequencia[texto[i]]++;
        i++;
    }
}

void imprimeTabelaFrequencia(unsigned int tabelaFrequencia[]){
    int i;

    printf("\nTabela de frequencia:\n");
    printf("\nNum ASCII = frequencia = caractere\n");

    for(i=0; i<TAM; i++){
        if(tabelaFrequencia[i] != 0)
            printf("\t%d = %d = %c\n", i, tabelaFrequencia[i], i);
    }
}