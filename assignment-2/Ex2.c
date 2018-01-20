/* CS260 - Assignment 2 - EX 2*/
/* Name:
 * Date:
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define bool int
#define true 1
#define false 0

void swap(int *numbers, int a, int b) {
    int tmp = numbers[a];
    numbers[a] = numbers[b];
    numbers[b] = tmp;
}

// Bubble sort
void sort(int *numbers, int n) {
    bool swapped = false;
    do {
        swapped = false;
        int i;
        for (i = 0; i < n - 1; i++) {
            if (numbers[i] > numbers[i + 1]) {
                swap(numbers, i, i + 1);
                swapped = true;
            }
        }
    } while (swapped);
}

void print_array(int *numbers, int n) {
    printf("[%d", numbers[0]);

    int i;
    for (i = 1; i < n; i++) {
        printf(", %d", numbers[i]);
    }

    printf("]");
}

int main() {
    /*Declare an integer n and assign it the value 20.*/
    int n = 20;

    /*Allocate memory for n integers using malloc.*/
    int* ns = (int*) malloc(sizeof(int) * n);

    /*Generate random integers (between 0 1nd 100) for the array, using rand().*/
    srand(time(NULL));
    int i;
    for (i = 0; i < n; i++) {
        ns[i] = rand() % 100;
    }

    /*Print the contents of the array.*/
    print_array(ns, n);
    printf("\n");

    /*Pass this array along with n to the sort() function*/
    sort(ns, n);

    /*Print the contents of the sorted array.*/
    print_array(ns, n);
    printf("\n");    

    return 0;
}
