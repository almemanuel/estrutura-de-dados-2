#include <stdio.h>
#include <stdlib.h>
#include "mtwister.c"
#include "structs.c"

int main() {
    MTRand r = seedRand(1234567);
    BlocoNaoMinerado bloco_nao_minerado;

    bloco_nao_minerado.numero = 1;
    bloco_nao_minerado.nonce = 4;

    float rand = genRand(&r);
    unsigned char text[16];
    sprintf(text, "%f", rand);
    printf("%s\n", text);
    unsigned char data[184];

    int real_size_of_data = 0;
    for(int i = 0; text[i] != '\0'; i++) {
        real_size_of_data++;
    }

    for(int i = 0 - real_size_of_data; i < 184; i++) {
        if(184 - i < real_size_of_data) {
            data[i] = text[i - real_size_of_data];
        } else {
            data[i] = (char)0;
        }
    }

    for(int i = 0; data[i] < '\0'; i++) {
      printf("%c", data[i]);
    }
    printf("%ld\n", sizeof(data));
    // // char data[184] = {0};
    // *(data + 184 - sizeof(rand)) = rand;
    // printf("%s\n", data);
    // // bloco_nao_minerado.data = (unsigned char)genRand(&r);
    // bloco_nao_minerado.hashAnterior = SHA256((unsigned char *)&zero, sizeof(bloco_nao_minerado), hash);
  return 0;
}