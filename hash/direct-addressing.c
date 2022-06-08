#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct Node *List;

void inicialized_array(int *array, int size) {
    if(size - 1 < 0) {
        return;
    } else {
        array[size - 1] = -1;
        inicialized_array(array, size - 1);
    }
}


void print_hash(int *array, int size) {
    for(int i = 0; i < size; i++) {
        printf("%d", *(array + i));
    }
    printf("\n");
}


void direct_addressing(int *array, int size, int key) {
    int index = key % size;
    for(int i = 0; i < size; i++) {
        if(*(array + index) == -1) {
            *(array + index) = key;
            break;
        } else if(*(array + index) == key) {
            printf("%d is in the array\n", key);
            return;
        } else {
            index = (index + i) % size;
        }
    }
}


int search_hash(int *array, int size, int key) {
    int index = key % size;

    for(int i = 0; i < size; i++) {
        if(*(array + index) == key) {
            return index;
        } else {
            index = (index + i) % size;
        }
    }
    return -1;
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
    search_hash(arr, n, key);
}