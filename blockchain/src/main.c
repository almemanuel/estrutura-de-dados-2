#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils/mtwister.c"
#include "utils/structs.c"

void print_hash(unsigned char *hash) {
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", *(hash + i));
    }
    printf("\n");
}

void search_hash(int block_number, FILE *fp) {
    BlocoMinerado block;
    fseek(fp, SEEK_SET, 0);
    for(int i = 0; !feof(fp) || i <= block_number; i++) {
        fread(&block, sizeof(BlocoMinerado), 1, fp);
        if(block.bloco.numero == block_number) {
            print_hash(block.hash);
            return;
        }
    }
    printf("Bloco não encontrado\n");
}

void max_bitcoin_hash(FILE *fp) {
    BlocoMinerado block, max_block;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    fseek(fp, SEEK_SET, 0);
    int max = 0, quantity;
    for(int i = 0; !feof(fp); i++) {
        fread(&block, sizeof(BlocoMinerado), 1, fp);
        quantity = (int) block.bloco.data[182] * 10 + (int) block.bloco.data[183];
        if(quantity > max && block.hash[0] == 0) {
            max = quantity;
            max_block = block;
            memcpy(hash, block.hash, SHA256_DIGEST_LENGTH);
        }
    }
    print_hash(hash);
}

int bitcoins_mined(FILE *fp, int block_number) {
    BlocoMinerado block;
    fseek(fp, SEEK_SET, 0);
    for(int i = 0; !feof(fp); i++) {
        fread(&block, sizeof(BlocoMinerado), 1, fp);
        if(block.bloco.numero == block_number) {
            return block.bloco.data[182] + block.bloco.data[183];
        }
    }
    return -1;
}

int main(){
    BlocoMinerado block[2];
    FILE *fp;
    fp = fopen("blocks", "rb");
    if(fp == NULL){
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    unsigned int option;
    do {
        printf("Selecione uma opção:\n");
        printf("1 - Consultar hash pelo número do bloco\n");
        printf("2 - Bitcoins por bloco\n");
        printf("3 - Hash com mais bitcoins\n");
        scanf("%i", &option);

        switch(option) {
            case 1: {
                unsigned int block_number;
                printf("Digite o número do bloco: ");
                scanf("%d", &block_number);
                search_hash(block_number, fp);
                break;
            }
            case 2: {
                unsigned int block_number;
                printf("Digite o hash: ");
                scanf("%i", &block_number);
                printf("Será impresso -1 caso não encontre o bloco\n");
                printf("%i\n", bitcoins_mined(fp, block_number));
                break;
            }
            case 3:
                max_bitcoin_hash(fp);
                break;
            default:
                printf("Saindo...\n");
                break;
        }
    } while(option != 0);

    fclose(fp);
    return 0;
}