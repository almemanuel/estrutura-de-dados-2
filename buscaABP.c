#include <stdio.h>
#include <stdlib.h>

struct TNoABP {
	int chave;
	struct TNoABP *esq, *dir;
};
typedef struct TNoABP TNoABP;


TNoABP **buscaPP(TNoABP **raiz, int k){
	TNoABP *no = *raiz;

	if(no == NULL) return NULL;
	if(no->chave == k) return raiz;
	if(k < no->chave){
		return buscaPP(&(no->esq), k );
	} else {
		return buscaPP(&(no->dir), k);
	}
}


int main(){
	TNoABP *raiz = NULL;
	TNoABP **pp = buscaPP(&raiz, 6);
}
