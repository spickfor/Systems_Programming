// sort.c

// Use sum.c as the basis for a C program called sort.c, which uses qsort to implement a basic version of sort:

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBERS 1024 // (1<<10)

// given function for last input into qsort
int compare_ints(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;

    return ia - ib; 
}

// given function for user input from sum.c file
size_t read_numbers(FILE *stream, int numbers[], size_t n) {
    size_t i = 0;

    while (i < n && scanf("%d", &numbers[i]) != EOF) {
        i++;
    }

    return i;
}

int main(int argc, char *argv[]) {

    // the format for qsort:   void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
    // base: pointer to first element of array to be sorted
    // nmemb: The number of elements in array
    // size: size in bytes of each element in array
    // campar: a function pointer to a comparison function that is used to compare two elements in the array

    int numbers[MAX_NUMBERS];
    size_t nsize;

    nsize = read_numbers(stdin, numbers, MAX_NUMBERS);
    qsort(numbers,nsize,sizeof(int),compare_ints);

    for (size_t i =0; i < nsize; i++) {
        printf("%d\n",numbers[i]);
    }


    return 0;
}