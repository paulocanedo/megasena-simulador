#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>

#define MAX_VALUE 60
#define MEGASENA_QTD_NUM 6

int randomNumber() {
    return (rand() % (MAX_VALUE)) + 1;
}

void sortNumbers(int *numbers, int length) {
    if(length <= 1) return;

    int sorted;
    do {
        sorted = 1;
        for(int i=0; i<length-1; i++) {
            int current = numbers[i];
            int next = numbers[i+1];

            if(next < current) {
                sorted = 0;
                numbers[i] = next;
                numbers[i+1] = current;
            }
        }
    } while(sorted == 0);
}

int containsNumber(int *numbers, int length, int search) {
    for(int i=0; i<length; i++) {
        if(numbers[i] == search) {
            return 1;
        }
    }
    return 0;
}

int indexOf(int search, int *numSet, int length) {
    for (int i = 0; i < length; i++) {
        if (search == numSet[i]) {
            return i;
        }
    }
    return -1;
}

int compareNumbers(int *numRef, int *numComp, int lenRef, int lenComp) {
    sortNumbers(numRef, lenRef);
    sortNumbers(numComp, lenComp);

    int count = 0;
    for(int i=0; i<lenRef; i++) {
        int idx = indexOf(numRef[i], numComp, lenComp);
        if(idx >= 0) count++;
    }
    return count;
}

int randomNumbers(int* numbers, int length) {
    int generated = 0;
    while(generated < length) {
        int number = randomNumber();
        if(0 == containsNumber(numbers, length, number)) {
            numbers[generated++] = number;
        }
    }
}

int* allocRandomNumbers(int length) {
    int *numbers = (int*) malloc(sizeof(int) * length);
    randomNumbers(numbers, length);
    return numbers;
}

void deallocRandomNumbers(int *numbers) {
    free(numbers);
    numbers = 0;
}

void printNumbers(int *numbers, int length) {
    for(int i=0; i<length; i++) {
        if(i ==0) {
            printf("%d", numbers[i]);
        } else {
            printf(", %d", numbers[i]);
        }
    }
    printf("\n");
}

int main() {
    srand(time(0));

    const int length = 11;
    
    int* sorteioOficial = allocRandomNumbers(MEGASENA_QTD_NUM);
    sortNumbers(sorteioOficial, MEGASENA_QTD_NUM);
    printf("Sorteio oficial: ");
    printNumbers(sorteioOficial, MEGASENA_QTD_NUM);

    int count = 0;
    // for(;;)
    // for (int i = 0; i < INT_MAX; i++)
    for (int success = 0; success < 100;)
    {
        int *sorteio = allocRandomNumbers(length);
        ++count;
        if(compareNumbers(sorteioOficial, sorteio, MEGASENA_QTD_NUM, length) == 6) {
            printf("%d\n", count);
            // printf("sorteio premiado depois de %d\n", count);
            count = 0;
            success++;
        }

        deallocRandomNumbers(sorteio);
    }

    deallocRandomNumbers(sorteioOficial);

    printf("\n");
}
