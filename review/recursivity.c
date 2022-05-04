#include <stdio.h>
#include <stdlib.h>

unsigned int fat(unsigned int n) {
  if (n == 0)
    return 1;
  return n*fat(n-1);
}


unsigned int fibonacci(unsigned int n)
{
    if(n == 1) return 0;
    if(n == 2) return 1;
    return fibonacci(n - 2) + fibonacci(n - 1);
}


int  sequencialSearch(int *v, int i, int k) {
    if (k == *v) return i;
    v++;
    i++;
    if(*v) return sequencialSearch(v, i, k);
    return -1;
}
