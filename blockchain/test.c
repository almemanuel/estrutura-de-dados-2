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
    unsigned char temp_hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *) block, sizeof(BlocoNaoMinerado), temp_hash);
    do {
        if(temp_hash[0] < 16) {
            memcpy(hash, temp_hash, SHA256_DIGEST_LENGTH);
            break;
        }
        block->nonce++;
        SHA256((unsigned char *) block, sizeof(BlocoNaoMinerado), temp_hash);
    } while(block->nonce < nonce_limit);

    do {
        SHA256((unsigned char *) block, sizeof(BlocoNaoMinerado), temp_hash);
        if(temp_hash[0] == 0) {
            memcpy(hash, temp_hash, SHA256_DIGEST_LENGTH);
            break;
        }
        block->nonce++;
        SHA256((unsigned char *) block, sizeof(BlocoNaoMinerado), temp_hash);
    } while(block->nonce < nonce_limit);

    do {
        SHA256((unsigned char *) block, sizeof(BlocoNaoMinerado), temp_hash);
        if(temp_hash[0] == 0 && temp_hash[1] < 16) {
            memcpy(hash, temp_hash, SHA256_DIGEST_LENGTH);
            break;
        }
        block->nonce++;
        SHA256((unsigned char *) block, sizeof(BlocoNaoMinerado), temp_hash);
    } while(block->nonce < nonce_limit);

    do {
        SHA256((unsigned char *) block, sizeof(BlocoNaoMinerado), temp_hash);
        if(temp_hash[0] == 0 && temp_hash[1] == 0) {
            memcpy(hash, temp_hash, SHA256_DIGEST_LENGTH);
            return;
        }
        block->nonce++;
        SHA256((unsigned char *) block, sizeof(BlocoNaoMinerado), temp_hash);
    } while(block->nonce < nonce_limit);
}

void print_block(BlocoMinerado *block) {
    printf("\n############################################################################################\n");
    printf("Block #%i\n", block->bloco.numero);
    printf("Block Hash: ");
    print_hash(block->hash);
    printf("Nonce: %i\n", block->bloco.nonce);
    printf("Data: %s\n", block->bloco.data);
    printf("Previous Hash: ");
    print_hash(block->bloco.hashAnterior);
    printf("###########################################################################################\n");
}


int main() {
    BlocoNaoMinerado bloco_nao_minerado[2];
    BlocoMinerado bloco_minerado[2];

    int count = 1;
    MTRand r = seedRand(1234567);

    int control = 0;
    printf("You can stop the minering when count % 10 == 0, or break the program with ctrl + c\n");
    while(control == 0) {
        bloco_nao_minerado[count % 2].numero = count;
        if(count == 1) {
            fill_data(bloco_nao_minerado[count % 2].data, &r);
            fill_genesis(bloco_nao_minerado[count % 2].hashAnterior, 184);
            search_nonce(&bloco_nao_minerado[count % 2], bloco_minerado[count % 2].hash);
            bloco_minerado[count % 2].bloco = bloco_nao_minerado[count % 2];
            print_block(&bloco_minerado[count % 2]);
        } else if(count % 2 == 0) {
            bloco_nao_minerado[count % 2].numero = count;
            fill_data(bloco_nao_minerado[count % 2].data, &r);
        // função get_back_hash
            memcpy(bloco_nao_minerado[count % 2].hashAnterior, bloco_minerado[count % 2 + 1].hash, SHA256_DIGEST_LENGTH);
            search_nonce(&bloco_nao_minerado[count % 2], bloco_minerado[count % 2].hash);
            bloco_minerado[count % 2].bloco = bloco_nao_minerado[count % 2];
            print_block(&bloco_minerado[count % 2]);
        } else if(count % 2 == 1) {
            bloco_nao_minerado[count % 2].numero = count;
            fill_data(bloco_nao_minerado[count % 2].data, &r);
        // função get_back_hash
            memcpy(bloco_nao_minerado[count % 2].hashAnterior, bloco_minerado[count % 2 - 1].hash, SHA256_DIGEST_LENGTH);
            search_nonce(&bloco_nao_minerado[count % 2], bloco_minerado[count % 2].hash);
            bloco_minerado[count % 2].bloco = bloco_nao_minerado[count % 2];
            print_block(&bloco_minerado[count % 2]);
            // testando escrita no arquivo
            FILE *file = fopen("blocks", "ab+");
            if(file == NULL) {
                printf("Erro ao abrir arquivo\n");
                return 1;
            }
            fwrite(bloco_minerado, sizeof(bloco_minerado), sizeof(bloco_minerado), file);
            fclose(file);
        }
        count++;
        if(count % 10 == 0) {
            printf("Continue? (0 - yes, Other - no)\n");
            scanf("%i", &control);
        }
    }


// //   //   // // bloco_nao_minerado.data = (unsigned char)genRand(&r);
// //   //   // bloco_nao_minerado.hashAnterior = SHA256((unsigned char *)&zero, sizeof(bloco_nao_minerado), hash);
// //   // return 0;
}