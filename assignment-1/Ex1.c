/* CS260 - Assignment 1 - EX 1*/
/* Name: Ethan Jones
 * Date: 9-1-2018
 * Solution description: Pointer stuff
 */
 
#include <stdio.h>
#include <stdlib.h>

void foo(int* ptr);

int main() {
    /*declare an integer x*/
    int x = 42069;
    
    /*print the address of x*/
    printf("Address of x: %p\n", &x);
    
    /*Call foo() with the address of x*/
    foo(&x);
    
    /*print the value of x*/
    printf("Value of x: %d\n", x);
    
    return 0;
}

void foo(int* ptr) {
    /*Print the value pointed to by ptr*/
    printf("Value pointed to by ptr: %d\n", *ptr); 
     
    /*Print the address pointed to by ptr*/
    printf("Address pointed to by ptr: %p\n", ptr);
     
    /*Print the address of ptr itself*/
    printf("Address of ptr: %p\n", &ptr);
}
