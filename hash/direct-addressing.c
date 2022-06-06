#include <stdio.h>
#include <stdlib.h>

void inicialized_array(int *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = -1;
    }
}


void direct_addressing(int *array, int size, int key) {
    int index = key % size;
    for(int i = 0; i < size; i++) {
        if(array[index] == -1) {
            array[index] = key;
            break;
        } else if(array[index] == key) {
            printf("%d is in the array\n", key);
            return;
        } else {
            index = (index + i) % size;
        }
    }
}


void search_hash(int *array, int size, int key) {
    int index = key % size;
    for(int i = 0; i < size; i++) {
        if(array[index] == key) {
            printf("%d is in the array\n", key);
            return;
        } else {
        index = (index + i) % size;
        }
    }
    printf("%d is not in the array\n", key);
}

int main() {
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    inicialized_array(arr, n);

    int element;
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &element);
        direct_addressing(arr, n, element);
    }

    int key;
    printf("Enter the key to be searched: ");
    scanf("%d", &key);
    search_hash(arr, n, key);
}