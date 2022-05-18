#include <stdio.h>
#include <stdlib.h>

struct TNoABP {
	int chave;
	struct TNOABP *dir, *esq;
}

typedef struct TNoABP TNoABP;

// cont = 0 na primeira chamada
void contaFolhas(TNoABP *raiz, int *cont){
	if(!raiz) return;
	if(!(raiz->esq) && !(raiz->dir)) (*cont)++;

	contaFolhas(raiz->esq, cont);
	contaFolhas(raiz->dir, cont);
}

/****************************************************************/
/*			COMPLEXIDADE LINEAR			*/
/* Tamanho do problema: n					*/
/* Quantidade fixa de comandos por chamada recursiva		*/
/* Reduz o problema em 1 a cada chamada				*/
/****************************************************************/
void linear(int n){
	if(n <= 0) return;
	printf("%i\n", n);
	linear(n - 1);
}


/****************************************************************/
/*			COMPLEXIDADE LOGARITMICA		*/
/* Reduz o problema pela metade a cada chamada			*/
/****************************************************************/
void logartimica(int n){
	if(n <= 0) return;
	printf("%i\n", n);
	logaritmica(n / 2);
}

/****************************************************************/
/* 			COMPLEXIDADE QUADRÁTICA			*/
/* Computações por chamada: n					*/
/* Reduz o problema em n - 1 por chamada			*/
/****************************************************************/
void nquadrado(int n){
	if(n <= 0) return;

	int i = 0;

	for(i = 0; i < n; ++i)
		printf("%i\n", n);
	quadrado(n - 1);
}


/*****************************************************************/
/* 			COMPLEXIDADE NLOG(N)			 */
/* Gera 2 novos problemas com tamanho n / 2 por chamada		 */
/*****************************************************************/
void nlogn(int n){
	if(n <= 0) return;

	int i = 0;

	for(i = 0; i < n; ++i)
		printf("%i\n", n);
	nlogn(n / 2);
	nlogn(n / 2);
}
