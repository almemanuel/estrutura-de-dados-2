/* RM 11:36 */

/************************************************************/
/*  Disciplina: Estrutura de Dados 2                        */
/*  Professor: Dr. Saulo Jorge Beltrão Queiroz              */
/*  Aluno: Emanuel de Almeida Souza                         */
/************************************************************/

#include <stdio.h>
#include <stdlib.h>


struct TNoABP {
    int chave;
    struct TNoABP *esq, *dir;
};

typedef struct TNoABP TNoABP;


TNoABP *alocaNo(int k) {
    TNoABP *no;
    no = (TNoABP *)malloc(sizeof(TNoABP));

    if(no == NULL) return NULL;
    no->chave = k;
    no->esq = no->dir = NULL;
    return no;
}


TNoABP *insereNoABP(TNoABP **raiz, int k){
    if(*raiz == NULL) *raiz = alocaNo(k);
    else if((*raiz)->chave > k) (*raiz)->esq = insereNoABP(&(*raiz)->esq, k);
    else if((*raiz)->chave < k) (*raiz)->dir = insereNoABP(&(*raiz)->dir, k);

    return *raiz;
}


int buscaNoABP(TNoABP *raiz, int k){
    if(raiz == NULL) return 0;
    else if(raiz->chave == k) return 1;
    else if(raiz->chave > k) return buscaNoABP(raiz->esq, k);
    else if(raiz->chave < k) return buscaNoABP(raiz->dir, k);
}


TNoABP **buscaPP(TNoABP **raiz, int k){
    if(*raiz == NULL) return NULL;
    else if((*raiz)->chave == k) return &*raiz;
    else if((*raiz)->chave < k) return buscaPP(&(*raiz)->dir, k);
    else if((*raiz)->chave > k) return buscaPP(&(*raiz)->esq, k);

    return NULL;
}


TNoABP **ppMenor(TNoABP **raiz){
    if((*raiz)->dir == NULL) return &*raiz;

    return ppMenor(&(*raiz)->dir);
}


void removeNoABP(TNoABP **raiz, int k){
    TNoABP **pp = buscaPP(raiz, k);

    if(pp == NULL) return;
    else if((*pp)->dir == NULL && (*pp)->esq == NULL){
        free(*pp);
        *pp = NULL;
        return;
    } else if(((*pp)->dir == NULL) != ((*pp)->esq == NULL)){
        TNoABP *filho = NULL;
        filho = (*pp)->esq == NULL ? (*pp)->dir : (*pp)->esq;
        free(*pp);
        *pp = filho;
        return;
    } else if((*pp)->esq && (*pp)->dir){
        TNoABP **pps = ppMenor(&((*raiz)->dir));
        (*pp)->chave = (*pps)->chave;
        free(*pps);
        (*pps) = NULL;
    }
}


void emOrdem(TNoABP *raiz) {
    if(raiz != NULL) {
        emOrdem(raiz->esq);
        printf("%d\n", raiz->chave);
        emOrdem(raiz->dir);
    }
}

/* RM 11:36 */
