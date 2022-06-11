#include <stdio.h>
#include "mtwister.c"

int main() {
  MTRand r = seedRand(1234567);
  int i;
  for(i=0; i<10; i++) {
    printf("%f\n", genRand(&r));
  }
  return 0;
}