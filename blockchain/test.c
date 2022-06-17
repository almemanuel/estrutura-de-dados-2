#include <stdio.h>
#include <stdlib.h>
#include "mtwister.c"
#include "structs.c"

int main() {
    BlocoNaoMinerado bloco_nao_minerado;

    bloco_nao_minerado.numero = 1;
    bloco_nao_minerado.nonce = 4;

    /***************************************************************/
    // transformar este trecho para ser uma função que preencha o campo data com 184 caracteres

    // transforma um float pseudoaleatório em uma string de caracteres
    // float rand = genRand(&r);
    MTRand r = seedRand(1234567);
    unsigned char rand[16];
    sprintf(rand, "%f", genRand(&r));

    // descobre o tamanho real da string do valor acima
    int rand_size = strlen(rand);

    // preenche o campo data com vários zeros e a string acima
    // se preencher uma string com o caractere 0, será entendido /0. é necessário converter 48 (correspondente a 0 na ASCII) para caractere
    for(int i = 0; i < 184 - rand_size; i++) {
        bloco_nao_minerado.data[i] = (unsigned char) 48;
    }
    strcpy(bloco_nao_minerado.data + 184 - rand_size, rand);
    /***************************************************************/

    printf("%ld\n", sizeof(bloco_nao_minerado.data));
    printf("%s\n", bloco_nao_minerado.data);

    // testando escrita no arquivo
    FILE *file = fopen("test.txt", "ab+");
    fwrite(bloco_nao_minerado.data, sizeof(bloco_nao_minerado.data), 184, file);
    fgets(bloco_nao_minerado.data, 184, file);
    printf("%s\n", bloco_nao_minerado.data);

    fclose(file);

    // // bloco_nao_minerado.data = (unsigned char)genRand(&r);
    // bloco_nao_minerado.hashAnterior = SHA256((unsigned char *)&zero, sizeof(bloco_nao_minerado), hash);
  return 0;
}