#include <stdio.h>
#include <stdlib.h>
#include "openssl/crypto.h" // SHA256_DIGEST_LENGTH
#include "openssl/sha.h"    // função SHA256
#include <openssl/sha.h>
#include "mtwister.c"
#include "structs.c"

int main() {
    BlocoNaoMinerado bloco_nao_minerado;

    bloco_nao_minerado.numero = 0;
    bloco_nao_minerado.nonce = 0;

    for(int i = 0; i < 184; i++) {
        bloco_nao_minerado.data[i] = (unsigned char) 48;
    }

    printf("%ld\n", sizeof(bloco_nao_minerado.hashAnterior));
    printf("%s\n", bloco_nao_minerado.data);

    // // bloco_nao_minerado.data = (unsigned char)genRand(&r);
    return 0;
}