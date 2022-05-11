/* RM 11:36 */

/************************************************************/
/*  Disciplina: Estrutura de Dados 2                        */
/*  Professor: Dr. Saulo Jorge Beltrão Queiroz              */
/*  Aluno: Emanuel de Almeida Souza                         */
/************************************************************/

#include <stdio.h>
#include <stdlib.h>


struct TNoAVL {
    int chave;
    struct TNoAVL *esq, *dir;
    int fb;
};

typedef struct TNoAVL TNoAVL;


TNoAVL *alocaNo(int k) {
    TNoAVL *no;
    no = (TNoAVL *)malloc(sizeof(TNoAVL));

    if(no == NULL) return NULL;
    no->chave = k;
    no->esq = no->dir = NULL;
    no->fb = 0;
    return no;
}

// o nó a ser rotacionado deve ter filho a direita
void rotacaoDireita(TNoAVL **no) {
    if(*no == NULL) return;
    TNoAVL *aux = *no;
    *no = aux->esq;
    aux->esq = (*no)->dir;
    (*no)->dir = aux;
}

// o nó a ser rotacionado deve ter filho a esquerda
void rotacaoEsquerda(TNoAVL **no) {
    if(*no == NULL) return;
    TNoAVL *aux = *no;
    *no = aux->dir;
    aux->dir = (*no)->esq;
    (*no)->esq = aux;
}

// implementar as funções de inserção e remoção
// por enquanto, as que estão aqui são de ABP
// TNoAVL *insereNoABP(TNoAVL **raiz, int k){
//     if(*raiz == NULL) *raiz = alocaNo(k);
//     else if((*raiz)->chave > k) (*raiz)->esq = insereNoABP(&(*raiz)->esq, k);
//     else if((*raiz)->chave < k) (*raiz)->dir = insereNoABP(&(*raiz)->dir, k);

//     return *raiz;
// }


// int buscaNoABP(TNoAVL *raiz, int k){
//     if(raiz == NULL) return 0;
//     else if(raiz->chave == k) return 1;
//     else if(raiz->chave > k) return buscaNoABP(raiz->esq, k);
//     else if(raiz->chave < k) return buscaNoABP(raiz->dir, k);
// }


// TNoAVL **buscaPP(TNoAVL **raiz, int k){
//     if(*raiz == NULL) return NULL;
//     else if((*raiz)->chave == k) return &*raiz;
//     else if((*raiz)->chave < k) return buscaPP(&(*raiz)->dir, k);
//     else if((*raiz)->chave > k) return buscaPP(&(*raiz)->esq, k);

//     return NULL;
// }


// TNoAVL **ppMenor(TNoAVL **raiz){
//     if((*raiz)->dir == NULL) return &*raiz;

//     return ppMenor(&(*raiz)->dir);
// }


// void removeNoABP(TNoAVL **raiz, int k){
//     TNoAVL **pp = buscaPP(raiz, k);

//     if(pp == NULL) return;
//     else if((*pp)->dir == NULL && (*pp)->esq == NULL){
//         free(*pp);
//         *pp = NULL;
//         return;
//     } else if(((*pp)->dir == NULL) != ((*pp)->esq == NULL)){
//         TNoAVL *filho = NULL;
//         filho = (*pp)->esq == NULL ? (*pp)->dir : (*pp)->esq;
//         free(*pp);
//         *pp = filho;
//         return;
//     } else if((*pp)->esq && (*pp)->dir){
//         TNoAVL **pps = ppMenor(&((*raiz)->dir));
//         (*pp)->chave = (*pps)->chave;
//         free(*pps);
//         (*pps) = NULL;
//     }
// }


// void emOrdem(TNoAVL *raiz) {
//     if(raiz != NULL) {
//         emOrdem(raiz->esq);
//         printf("%d\n", raiz->chave);
//         emOrdem(raiz->dir);
//     }
// }

/* RM 11:36 */
