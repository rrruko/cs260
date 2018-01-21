/* CS260 - Assignment 1 - EX 2*/
/* Name: Ethan Jones
 * Date: 9-1-2018
 * Solution description: More pointer stuff
 */

#include <stdio.h>
#include <stdlib.h>

int bar(int* a, int* b, int c){
    /*Set a to double its original value*/
    *a *= 2;

    /*Set b to half its original value*/
    *b /= 2;

    /*Assign a+b to c*/
    c = *a + *b;

    /*Return c*/
    return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 11, 12, & 13 respectively*/
    int x = 11;
    int y = 12;
    int z = 13;

    /*Print the values of x, y and z*/
    printf("x: %d\n", x);
    printf("y: %d\n", y);
    printf("z: %d\n", z);

    /*Call bar() appropriately, passing x,y,z as parameters*/
    /*Print the value returned by bar from this function call*/
    printf("Bar(x,y,z) returns %d\n", bar(&x, &y, z));

    /*Print the values of x, y and z again*/
    printf("x: %d, y: %d, z: %d.\n", x, y, z);

    /*Is the return value different than the value of z?  Why?
	Express your short answer at the bottom of the file as a comment.*/
    return 0;
}

/* The return value is different because z was not passed as a pointer so bar
 * doesn't have write access to it.
 */
