#include <stdio.h>
#include <stdlib.h>
#include "../include/tabelaFrequencia.h"
#include "../include/listaEncadeadaOrdenada.h"

void criaLista(Lista *li){
    li->inicio = NULL;
    li->tam = 0;
}

void insereOrdenado(Lista *li, No *no){
    No *aux;
    //se a lista esta vazia
    if(li->inicio == NULL){
        li->inicio = no;
    }
    //tem freq menor que o inicio
    else if(no->freq < li->inicio->freq){
        no->prox = li->inicio;
        li->inicio = no;
    }
    else{
        aux = li->inicio;
        while(aux->prox && aux->prox->freq <= no->freq)
            aux = aux->prox;
        no->prox = aux->prox;
        aux->prox = no;
    }

    li->tam++;
}

void preencheLista(unsigned int tab[], Lista *li){
    No *newNo;
    for(int i = 0; i < TAM; i++){
        if(tab[i] > 0){
            newNo = (No*)malloc(sizeof(No));
            if(newNo){
                newNo->caracter = i;
                newNo->freq = tab[i];
                newNo->dir = NULL;
                newNo->esq = NULL;
                newNo->prox = NULL;

                insereOrdenado(li, newNo);
            }
            else{
                printf("\nErro no preenchimento da lista\n");
                break;
            }
        }
    }
}

void imprimeLista(Lista *li){
    No *aux = li->inicio;

    printf("\nTamanho lista:%d \n", li->tam);
    while(aux){
        printf("\nCaracter: %c Frequencia:%d", aux->caracter, aux->freq);
        aux = aux->prox;
    }
}