#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    // 4 zeros -> 0
    unsigned char data[4] = "0000";
    printf("%s\n", data);
    printf("%i: ", 0);
    printf("%04x\n", 0);

    // 3 zeros -> [1, 15]
    printf("%i: ", (unsigned int) pow(16, 0));
    printf("%04x\n", (unsigned int) pow(16, 0));
    printf("%i: ", (unsigned int) pow(16, 1) - 1);
    printf("%04x\n", (unsigned int) pow(16, 1) - 1);

    // 2 zeros -> [16, 255]
    printf("%i: ", (unsigned int) pow(16, 1));
    printf("%04x\n", (unsigned int) pow(16, 1));
    printf("%i: ", (unsigned int) pow(16, 2) - 1);
    printf("%04x\n", (unsigned int) pow(16, 2) - 1);

    // 1 zero -> [256, )
    printf("%i: ", (unsigned int) pow(16, 2));
    printf("%04x\n", (unsigned int) pow(16, 2));
}