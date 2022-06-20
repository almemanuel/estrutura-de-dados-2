#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mtwister.c"
#include "structs.c"


void print_hash(unsigned char *hash) {
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", *(hash + i));
    }
    printf("\n");
}

void fill_genesis(unsigned char *data, unsigned int total_zero) {
    // utilizar busca binária para preencher
    for(int i = 0; i < total_zero; i++) {
        *(data + i) = 0;
    }
}

void fill_with_zero(unsigned char *data, unsigned int total_zero) {
    // utilizar busca binária para preencher
    for(int i = 0; i < total_zero; i++) {
        *(data + i) = (unsigned char) 48;
    }
}

void fill_data(unsigned char *data, MTRand *r) {
    float rand_number;
    do {
        rand_number = genRand(r);
    } while(rand_number > 0.63);

    unsigned char rand_text[16];
    sprintf(rand_text, "%f", rand_number);
    rand_text[4] = '\0';
    strcpy(data + 184 - 3, (rand_text + 2));
    fill_with_zero(data, 184 - 3);
}

void search_nonce(BlocoNaoMinerado *block, unsigned char *hash) {
    block->nonce = 0;
    int nonce_limit = pow(2, 31) - 1;
    do {
        SHA256((unsigned char *) &block, sizeof(BlocoNaoMinerado), hash);
        if((hash[0] == 0) && (hash[1] == 0)) {
            SHA256((unsigned char *) &block, sizeof(BlocoNaoMinerado), hash);
            return;
        }
        block->nonce++;
    } while(block->nonce < nonce_limit);
}

void print_block(BlocoMinerado *block) {
    printf("############################################################################################\n");
    printf("Block #%i\n", block->bloco.numero);
    printf("Block Hash:");
    print_hash(block->hash);
    printf("Nonce: %i\n", block->bloco.nonce);
    printf("Data: %s\n", block->bloco.data);
    printf("Previous Hash:");
    print_hash(block->bloco.hashAnterior);
    printf("###########################################################################################\n");
}


int main() {
    BlocoNaoMinerado bloco_nao_minerado[2];

    bloco_nao_minerado[0].numero = 1;
    MTRand r = seedRand(1234567);
    fill_data(bloco_nao_minerado[0].data, &r);
    fill_genesis(bloco_nao_minerado[0].hashAnterior, 184);
    BlocoMinerado bloco_minerado[2];
    search_nonce(&bloco_nao_minerado[0], bloco_minerado[0].hash);
    bloco_minerado[0].bloco = bloco_nao_minerado[0];
    print_block(&bloco_minerado[0]);

    bloco_nao_minerado[1].numero = bloco_nao_minerado[0].numero + 1;
    fill_data(bloco_nao_minerado[1].data, &r);
    // função get_back_hash
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        *(bloco_nao_minerado[1].hashAnterior + i) = *(bloco_minerado[0].hash + i);
    }
    printf("\n PESQUISANDO NONCE...\n");
    search_nonce(&bloco_nao_minerado[1], bloco_minerado[1].hash);
    bloco_minerado[1].bloco = bloco_nao_minerado[1];
    print_block(&bloco_minerado[1]);

//     // Função minera bloco
//     BlocoMinerado bloco_minerado;
//     bloco_minerado.bloco = bloco_nao_minerado;
//     *(bloco_minerado.hash) = *hash;
//     printf("Informações do bloco minerado:\n");
//     printf("\tHash do bloco: ");
//     /***************************************************************/
//     /***************************************************************/
//     printf("\tBloco #%d\n", bloco_minerado.bloco.numero);
//     printf("\tNonce: %d\n", bloco_minerado.bloco.nonce);
//     printf("\tData: %s\n", bloco_minerado.bloco.data);
//     printf("\tHash Anterior: ");
//     for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
//         printf("%02x", bloco_minerado.bloco.hashAnterior[i]);
//     }
//     printf("\n");
//     /***************************************************************/
// //     // BlocoMinerado bloco_minerado;
// //     // bloco_minerado.bloco = bloco_nao_minerado;
// //     // printf("%ld\n", sizeof(bloco_nao_minerado));
// //     // SHA256((unsigned char *) &bloco_minerado.bloco, sizeof(bloco_minerado.bloco), bloco_minerado.hash);

// //     // // testando escrita no arquivo
// //     // FILE *file = fopen("test", "ab+");
// //     // fwrite(&bloco_minerado, sizeof(bloco_minerado), sizeof(bloco_minerado), file);
// //     // unsigned char bloco[256];
// //     // fgets(bloco, sizeof(bloco_minerado), file);
// //     // printf("%s\n", bloco);
// //     // printf("%ld\n", sizeof(bloco));

// //   //   fclose(file);

// //   //   // // bloco_nao_minerado.data = (unsigned char)genRand(&r);
// //   //   // bloco_nao_minerado.hashAnterior = SHA256((unsigned char *)&zero, sizeof(bloco_nao_minerado), hash);
// //   // return 0;
}