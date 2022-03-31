#include <stdlib.h>
#include <stdio.h>

struct TNoABP{
    int chave;
    struct TNoABP  *esq, *dir;
};

typedef struct TNoABP TNoABP;


/*
 * Recebe ponteiro de ponteiro para ABP e uma chave de insercao.
 * Devolve endereço do no inserido ou NULL
 * em caso de insucesso na insercao.
*/
TNoABP *insereNoABP(TNoABP **r, int k){
    if(*r == NULL){
        *r = (TNoABP *) malloc(sizeof(TNoABP));
        (*r)->chave = k;
        (*r)->esq = (*r)->dir = NULL;
    }
    else if((*r)->chave > k) (*r)->esq = insereNoABP(&(*r)->esq, k);
    else if((*r)->chave < k) (*r)->dir = insereNoABP(&(*r)->dir, k);
    return *r;

    return 0; //deixe como ultimo comando. Nunca sera executado.
}


/*
 * Recebe ponteiro para ABP e uma chave de busca.
 * Devolve 1 se existe um no cujo campo chave
 * seja igual a k ou 0 (zero) caso contrário.
*/
int buscaNoABP(TNoABP *r, int k){
    if(r->chave == k) return 1;
    else if(r->esq > k) return buscaNoABP(r->esq, k);
    else if(r->dir < k) return buscaNoABP(r->dir, k);
    return -1;//deixe como ultimo comando. Nunca sera executado.
}


TNoABP **buscaPP(TNoABP **raiz, int k){
    if((*raiz) == k) return *raiz;
    else if(r->esq > k) return buscaPP(*r->esq, k);
    else if(r->dir < k) return buscaPP(*r->dir, k);
    return NULL;
}

TNoABP **ppMenor(TNo ABP **raiz){
    if((*raiz)->dir == NULL) return *raiz;
    return ppMenor((*raiz)->dir);
}



/*
 * Recebe ponteiro de ponteiro para ABP e uma chave de remocao
 * e remove o no cujo campo chave seja igual a k.
 */
void removeNoABP(TNoABP **raiz, int k){
    TNoABP **pp = buscaPP(raiz, k);
    if((*pp)->dir == NULL && (*pp)->esq == NULL){
        free(*pp);
        *pp = NULL;
        return;
    }
    
    TNoABP *filho = NULL;
    if((*pp)->dir == NULL != (*pp)->esq == NULL){
        filho = (*pp)->esq == NULL ? (*pp)->dir : (*pp)->esq;
        free(*pp);
        *pp = filho;
        return;
    }

     if((*pp)->esq && (*pp)->dir){
        TNoABP **pps=ppMenor(&((*raiz)->dir));
        substituiDados(pp, (*pps)->chave);
        removeNoABP(pps, k);
    }
}

void emOrdem(TNoABP *raiz)
{
  if (raiz != NULL)
  {
    emOrdem(raiz->esq);
    printf("%d\n", raiz->chave);
    emOrdem(raiz->dir);
  }
}

int main()
{
  TNoABP *raiz = NULL; //arvore nascendo vazia
  int N, chave, i;
 
  //populando a arvore
  scanf("%d", &N); //numero de chaves a inserir
  for(i=0; i<N; ++i)
  {
    scanf("%d", &chave);    
    insereNoABP(&raiz, chave);    
  }
  emOrdem(raiz);//imprime toda arvore em ordem crescente.

  //buscando na arvore
  scanf("%d", &N); //numero de chaves a buscar
  for(i=0; i<N; ++i)
  {
    scanf("%d", &chave);    
    printf("%d\n", buscaNoABP(raiz, chave));
  }

  //removendo na arvore
  scanf("%d", &N);//numero de nos a remover
  for(i=0; i<N; ++i)
  {
    scanf("%d", &chave);    
    removeNoABP(&raiz, chave);
  }
  emOrdem(raiz);//imprime toda arvore em ordem crescente.
  return 0;
}