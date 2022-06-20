/* RM 11:36 */

/************************************************************/
/*  Exemplo de uso da funcao SHA256 da biblioteca Open SSL  */
/*  Este código requer a instalação do pacote libssl-dev    */
/*  Para compilar este código use gcc hash.c -lcrypto       */
/************************************************************/
/*  Código para explorar a geração de hash da SHA256        */
/*  Originalmente, pedia-se um valor inteiro e gerava o     */
/*  hash. Na atividade, o professor propos que, em vez de   */
/*  um inteiro, fosse lido uma struct desenvolvida pelo     */
/*  aluno.                                                  */
/************************************************************/
/*  Disciplina: Estrutura de Dados 2                        */
/*  Professor: Dr. Saulo Jorge Beltrão Queiroz              */
/*  Aluno: Emanuel de Almeida Souza                         */
/************************************************************/

#include "openssl/crypto.h" // SHA256_DIGEST_LENGTH
#include "openssl/sha.h"    // função SHA256
#include <string.h>

struct anything {
    char name[10];
    int age;
    float height;
    float weight;
}; typedef struct anything any;


void printHash(unsigned char hash[], int length) {
    int i;
    for(i=0;i<length;++i)
    printf("%02x", hash[i]);

    printf("\n");
}


int main(int argc, char *argv[]) {
    any structure;

    printf("Name: ");
    fgets(structure.name, 10, stdin);
    setbuf(stdin, NULL);

    do {
        printf("Age: ");
        scanf("%i", &structure.age);
    } while(structure.age < 0);

    do {
        printf("Height: ");
        scanf("%f", &structure.height);
    } while(structure.height <= 0);

    do {
        printf("Weight: ");
        scanf("%f", &structure.weight);
    } while(structure.weight <= 0);

    printf("\t\t<=====>\n");
    printf("Generating hash for this datas:");
    printf("\n\tAge: %i yo\n\tHeight: %.2f m\n\tWeidth: %.3f Kg\n\tName: %s", structure.age, structure.height, structure.weight, structure.name);
    printf("\t\t<=====>\n");

    //vetor que armazenará o resultado do hash. Tamanho definidio pela libssl
    unsigned char hash[SHA256_DIGEST_LENGTH];

    /************************************************************/
    /*  A funcao SHA256 requer tres parametros                  */
    /*  1. o ponteiro para um vetor de unsigned char contendo o */
    /*  dado cujo hash você deseja calcular                     */
    /*  2. o tamanho em bytes do dado cujo hash você deseja     */
    /*  calcular                                                */
    /*  3. o ponteiro para um vetor de unsigned char que        */
    /*  armazenará o resultado do hash calculado.               */
    SHA256((unsigned char *)&structure, sizeof(structure), hash);
    printf("Hash: ");
    printHash(hash, SHA256_DIGEST_LENGTH);

    return 0;
}

/* RM 11:36 */