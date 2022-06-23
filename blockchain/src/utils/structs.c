/* RM 11:36 */

/************************************************************/
/*  Disciplina: Estrutura de Dados 2                        */
/*  Professor: Dr. Saulo Jorge Beltrão Queiroz              */
/*  Aluno: Emanuel de Almeida Souza                         */
/************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "openssl/crypto.h" // SHA256_DIGEST_LENGTH
#include "openssl/sha.h"    // função SHA256
#include <string.h>

struct BlocoNaoMinerado {
    unsigned int numero;//4
    unsigned int nonce;//4
    unsigned char data[184];//nao alterar. Deve ser inicializado com zeros.
    unsigned char hashAnterior[SHA256_DIGEST_LENGTH]; //32
};
typedef struct BlocoNaoMinerado BlocoNaoMinerado;

struct BlocoMinerado {
    BlocoNaoMinerado bloco;
    unsigned char hash[SHA256_DIGEST_LENGTH]; //32 bytes
};
typedef struct BlocoMinerado BlocoMinerado;
/* RM 11:36 */