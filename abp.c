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

int isLeaf(TNoABP *node) {
    if(node == NULL) return -1; // empty tree
    else if(node->esq == NULL && node->dir == NULL) return 1; // the node is a leaf node
    return 0; // the node is not a leaf node
}

TNoABP *insertNode(TNoABP **node, int new_value) {
    if(*node == NULL){
        *node = (TNoABP *) malloc(sizeof(TNoABP));
        (*node)->chave = new_value;
        (*node)->esq = (*node)->dir = NULL;
    }
    else if((*node)->chave > new_value) (*node)->esq = insertNode(&(*node)->esq, new_value);
    else if((*node)->chave < new_value) (*node)->dir = insertNode(&(*node)->dir, new_value);
    return *node;
}

void printABP(TNoABP *raiz) {
    if (raiz == NULL) return;
    printABP(raiz->esq);
    printf("%d\n", raiz->chave);
    printABP(raiz->dir);
}


int main() {
    unsigned int n;
    do
        scanf("%i", &n);
    while(n == 0);

    TNoABP *raiz = NULL;

    int v[n], i;
    for(i = 0; i < n; i++){
        scanf("%i", &v[i]);
        raiz = insertNode(&raiz, v[i]);
    }

    printABP(raiz);

    return 0;
}