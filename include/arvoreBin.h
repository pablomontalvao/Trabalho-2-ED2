#include <stdio.h>
 #include <stdlib.h>
 
 typedef struct NO* ArvBin;
 
 ArvBin* cria_ArvBin();
 void libera_ArvBin(ArvBin *raiz);
 int insere_ArvBin(ArvBin* raiz, int valor);
 int remove_ArvBin(ArvBin *raiz, int valor);
 int estaVazia_ArvBin(ArvBin *raiz);
 int altura_ArvBin(ArvBin *raiz);
 int totalNO_ArvBin(ArvBin *raiz);
 int consulta_ArvBin(ArvBin *raiz, int valor);
 void preOrdem_ArvBin(ArvBin *raiz);
 void emOrdem_ArvBin(ArvBin *raiz);
 void posOrdem_ArvBin(ArvBin *raiz);
 
 struct NO{
 	int info;
 	struct NO *esq;
 	struct NO *dir;
 };
 
 ArvBin* cria_ArvBin(){
 	ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
 	if(raiz != NULL)
 		*raiz = NULL;
 	return raiz;
 }
 
 void libera_NO(struct NO* no){
 	if(no == NULL)
 		return;
 	libera_NO(no->esq);
 	libera_NO(no->dir);
 	free(no);
 	no = NULL;
 }
 
 void libera_ArvBin(ArvBin* raiz){
 	if(raiz == NULL)
 		return;
 	libera_NO(*raiz); // libera cada n�
 	free(raiz); // libera a raiz
 }
 
 int estaVazia_ArvBin(ArvBin *raiz){
 	if(raiz == NULL)
 		return 1;
 	if(*raiz == NULL)
 		return 1;
 	return 0;
 }
 
 int totalNO_ArvBin(ArvBin *raiz){
 	if (raiz == NULL)
 		return 0;
 	if (*raiz == NULL)
 		return 0;
 	int totalNO_esq = totalNO_ArvBin(&((*raiz)->esq));
 	int totalNO_dir = totalNO_ArvBin(&((*raiz)->dir));
 	return (totalNO_esq + totalNO_dir + 1);
 }
 
 int altura_ArvBin(ArvBin *raiz){
 	if (raiz == NULL)
 		return 0;
 	if (*raiz == NULL)
 		return 0;
 	int alt_esq = altura_ArvBin(&((*raiz)->esq));
 	int alt_dir = altura_ArvBin(&((*raiz)->dir));
 	if (alt_esq > alt_dir)
 		return (alt_esq + 1);
 	else
 		return(alt_dir + 1);
 }
 
 int insere_ArvBin(ArvBin* raiz, int valor){
 	if(raiz == NULL)
 		return 0;
 	struct NO* novo;
 	novo = (struct NO*) malloc(sizeof(struct NO));
 	if(novo == NULL)
 		return 0;
 	novo->info = valor;
 	novo->dir = NULL;
 	novo->esq = NULL;
 
 	if(*raiz == NULL)
 		*raiz = novo;
 	else{
 		struct NO* atual = *raiz;
 		struct NO* ant = NULL;
 
 		// Navega nos n�s da �rvore at� chegar em um n� folha
 		while(atual != NULL){
 			ant = atual;
 			if(valor == atual->info){
 				free(novo);
 				return 0; // elemento j� existe
 			}
 
 			if(valor > atual->info)
 				atual = atual->dir;
 			else
 				atual = atual->esq;
 		}
 
 		// Insere como filho desse n� folha
 		if(valor > ant->info)
 			ant->dir = novo;
 		else
 			ant->esq = novo;
 	}
 	return 1;
 }
 
 int consulta_ArvBin(ArvBin *raiz, int valor){
 	if (raiz == NULL)
 		return 0;
 	struct NO* atual = *raiz;
 	while (atual != NULL){
 		if (valor == atual->info){
 			return 1;
 		}
 		if (valor > atual->info)
 			atual = atual->dir;
 		else
 			atual = atual->esq;
 	}
 	return 0;
 }
 
 struct NO* remove_atual(struct NO* atual) {
 	struct NO *no1, *no2;
 
 	// Sem filho da esquerda. Apontar para o filho da direita (trata n� folha e n� com 1 filho).
 	if (atual->esq == NULL){
 		no2 = atual->dir;
 		free(atual);
 		return no2;
 	}
 
 	// Procura filho mais � direita na sub-�rvore da esquerda.
 	no1 = atual;
 	no2 = atual->esq;
 	while (no2->dir != NULL){
 		no1 = no2;
 		no2 = no2->dir;
 	}
 
 	// Copia o filho mais � direita na sub-�rvore da esquerda para o lugar do n� removido.
 	if (no1 != atual){
 		no1->dir = no2->esq;
 		no2->esq = atual->esq;
 	}
 	no2->dir = atual->dir;
 
 	free(atual);
 	return no2;
 }
 // http://www.ime.usp.br/~pf/algoritmos/aulas/binst.html
 int remove_ArvBin(ArvBin *raiz, int valor){
 	if (raiz == NULL)
 		return 0;
 	struct NO* ant = NULL;
 	struct NO* atual = *raiz;
 	while (atual != NULL){
         //Achou o n� a ser removido. Tratar o tipo de remo��o.
 		if (valor == atual->info){
 			if (atual == *raiz)
 				*raiz = remove_atual(atual);
 			else{
 				if (ant->dir == atual)
 					ant->dir = remove_atual(atual);
 				else
 					ant->esq = remove_atual(atual);
 			}
 			return 1;
 		}
 		// Continua buscando na �rvore n� a ser removido
 		ant = atual;
 		if (valor > atual->info)
 			atual = atual->dir;
 		else
 			atual = atual->esq;
 	}
 	return 0;
 }
 
 void preOrdem_ArvBin(ArvBin *raiz){
 	if(raiz == NULL)
 		return;
 	if(*raiz != NULL){
 		printf("%d\n",(*raiz)->info);
 		preOrdem_ArvBin(&((*raiz)->esq));
 		preOrdem_ArvBin(&((*raiz)->dir));
 	}
 }
 
 void emOrdem_ArvBin(ArvBin *raiz){
 	if(raiz == NULL)
 		return;
 	if(*raiz != NULL){
 		emOrdem_ArvBin(&((*raiz)->esq));
 		printf("%d\n",(*raiz)->info);
 		emOrdem_ArvBin(&((*raiz)->dir));
 	}
 }
 
 void posOrdem_ArvBin(ArvBin *raiz){
 	if(raiz == NULL)
 		return;
 	if(*raiz != NULL){
 		posOrdem_ArvBin(&((*raiz)->esq));
 		posOrdem_ArvBin(&((*raiz)->dir));
 		printf("%d\n",(*raiz)->info);
 	}
 }