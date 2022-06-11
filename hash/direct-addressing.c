#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct Node *List;

void inicialized_array(int *array, int size) {
    if(size == 0) {
        return;
    } else {
        *array = -1;
        inicialized_array(array + 1, size - 1);
    }
}


void print_hash(int *array, int size) {
    if(size == 0) {
        return;
    } else {
        printf("%d ", *array);
        print_hash(array + 1, size - 1);
    }
}


void direct_addressing(int *array, int size, int key) {
    if(size == 0) {
        printf("Fuller array\n");
        return;
    }

    int index = key % size;
    if(*(array + index) == -1) {
        *(array + index) = key;
    } else if(*(array + index) == key) {
        return;
    } else {
        return direct_addressing(array, size - 1, key);
    }
}


int search_hash(int *array, int size, int key) {
    if(size == 0) {
        return 0;
    }

    int index = key % size;
    if(*(array + index) == key) {
        return key % size;
    } else if(*(array + index) == -1) {
        return -1;
    } else {
        return search_hash(array + 1, size - 1, key);
    }
}

int main() {
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    inicialized_array(arr, n);
    print_hash(arr, n);

    int element;
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &element);
        direct_addressing(arr, n, element);
    }
    print_hash(arr, n);

    int key;
    printf("Enter the key to be searched: ");
    scanf("%d", &key);
    printf(" %i ", search_hash(arr, n, key));
}