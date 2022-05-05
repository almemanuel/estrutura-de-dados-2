/* RM 11:36 */

/************************************************************/
/*  Disciplina: Estrutura de Dados 2                        */
/*  Professor: Dr. Saulo Jorge Beltrão Queiroz              */
/*  Aluno: Emanuel de Almeida Souza                         */
/************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "abp.c"

int main() {
    TNoABP *raiz = NULL; //arvore nascendo vazia
    int N, chave, i;

    printf("Numero de nós: ");
    scanf("%d", &N);

    printf("Nós: ");
    for(i=0; i<N; ++i) {
      scanf("%d", &chave);
      insereNoABP(&raiz, chave);
      emOrdem(raiz);
    }

    printf("Numero de buscas: ");
    scanf("%d", &N);
    for(i=0; i<N; ++i) {
      printf("Pesquisar por: ");
      scanf("%d", &chave);
      printf("---\n1 - Sim | 0 - Não\nNó existe? %d\n", buscaNoABP(raiz, chave));
    }

    printf("Numero de remocoes: ");
    scanf("%d", &N);

    for(i=0; i<N; ++i) {
      printf("Remover: ");
      scanf("%d", &chave);
      removeNoABP(&raiz, chave);
      printf("\n:-----------------------------:\n");
      emOrdem(raiz);
    }
    return 0;
}

/* RM 11:36 */
