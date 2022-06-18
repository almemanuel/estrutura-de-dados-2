#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mtwister.c"
#include "structs.c"

int main() {
    BlocoNaoMinerado bloco_nao_minerado;

    bloco_nao_minerado.numero = 1;
    unsigned char transaction[3];
    MTRand r = seedRand(1234567);
    for(int i = 0; i < 10; i++) {
        float rand_number;
        do {
            rand_number = genRand(&r);
        } while(rand_number > 0.63);
        unsigned char rand_text[16];
        sprintf(rand_text, "%f", rand_number);
        rand_text[4] = '\0';
        strcpy(transaction, (rand_text + 2));
    }

    /***************************************************************/
    // utilizar busca binária para preencher
    for(int i = 0; i < 184 - 3; i++) {
        bloco_nao_minerado.data[i] = (unsigned char) 48;
    }
    strcpy(bloco_nao_minerado.data + 184 - 3, transaction);
    printf("%s\n", bloco_nao_minerado.data);
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        bloco_nao_minerado.hashAnterior[i] = (unsigned char) 48;
    }
    printf("%s\n", bloco_nao_minerado.hashAnterior);
    /***************************************************************/

    /***************************************************************/
    // encontrando nonce
    BlocoMinerado bloco_minerado;
    bloco_nao_minerado.nonce = 0;

    unsigned int flag = 0;
    do {
        SHA256((unsigned char *) &bloco_nao_minerado, sizeof(BlocoNaoMinerado), bloco_minerado.hash);
        for(int i = 0; i < 2; i++) {
            if(bloco_minerado.hash[i] != 0) {
                break;
            }
            if(i == 2) {
                printf("%d\n", bloco_nao_minerado.nonce);
                flag = 1;
            }
        }
        bloco_nao_minerado.nonce++;
    } while(flag == 0);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", bloco_minerado.hash[i]);
    }

//     bloco_nao_minerado.nonce = (unsigned int) (genRand(&r) * pow(10, 6));
//     printf("%d\n", bloco_nao_minerado.nonce);

//     unsigned char hash[SHA256_DIGEST_LENGTH];
//     SHA256(bloco_nao_minerado.data, sizeof(bloco_nao_minerado.data), hash);
//     for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
//         printf("%02x", hash[i]);
//     }

//     // BlocoMinerado bloco_minerado;
//     // bloco_minerado.bloco = bloco_nao_minerado;
//     // printf("%ld\n", sizeof(bloco_nao_minerado));
//     // SHA256((unsigned char *) &bloco_minerado.bloco, sizeof(bloco_minerado.bloco), bloco_minerado.hash);

//     // // testando escrita no arquivo
//     // FILE *file = fopen("test", "ab+");
//     // fwrite(&bloco_minerado, sizeof(bloco_minerado), sizeof(bloco_minerado), file);
//     // unsigned char bloco[256];
//     // fgets(bloco, sizeof(bloco_minerado), file);
//     // printf("%s\n", bloco);
//     // printf("%ld\n", sizeof(bloco));

//   //   fclose(file);

//   //   // // bloco_nao_minerado.data = (unsigned char)genRand(&r);
//   //   // bloco_nao_minerado.hashAnterior = SHA256((unsigned char *)&zero, sizeof(bloco_nao_minerado), hash);
//   // return 0;
}