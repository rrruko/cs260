/* CS260 - Assignment 2 - EX 3*/
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

typedef struct person {
	int age;
	char sex;
} person;

void swap(person* people, int a, int b) {
    person tmp = people[a];
    people[a] = people[b];
    people[b] = tmp;
}

// Bubble sort
void sort(person* people, int n) {
    /* Sort the given array of people by age, of length n */
    bool swapped = false;
    do {
        swapped = false;
        int i;
        for (i = 0; i < n - 1; i++) {
            if (people[i].age > people[i + 1].age) {
                swap(people, i, i + 1);
                swapped = true;
            }
        }
    } while (swapped);
}

/*This function can be identical to the previous sort function, however it needs to return the total number of comparisons carried out in the sort.
If you want to attempt to optimize the sort, then you are welcome to do so */

int sortAnalysis(person* people, int n) {
    /* Sort the given array of persons of length n
	Return the number of comparisons required to terminate the algorithm */
    /* Sort the given array of people by age, of length n */
    int comp_count = 0;
    bool swapped = false;
    do {
        swapped = false;
        int i;
        for (i = 0; i < n - 1; i++) {
            comp_count++;
            if (people[i].age > people[i + 1].age) {
                swap(people, i, i + 1);
                swapped = true;
            }
        }
    } while (swapped);
    return comp_count;
}

void display(person* people, int n) {
    /* Display information about the ten people in the format:
	  Person 1: Age: X, Gender: Y
	  ...
	  Person N: Age: X, Gender: Y
    */
    int i;
    for (i = 0; i < n; i++) {
        printf("Person %d: Age: %d, Gender: %c\n", i, 
            people[i].age, people[i].sex);
    }
}

int main() {
    srand(time(NULL));

    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;

    /*Allocate memory for an array of n persons using malloc.*/
    person* people = (person*) malloc(sizeof(person) * n);

    /*Fill this array with random persons with ages between 18 and 90 and random genders, using rand().*/
    int i;
    for (i = 0; i < n; i++) {
        int a = rand() % (90 - 18) + 18;
        int s = rand() % 2 == 0 ? 'M' : 'F';
        person p = { a, s };
        people[i] = p;
    }

    /*Pass this array along with n to the display() function.*/
    display(people, n);
    printf("---------------------- \n");
	
    /*Pass this array along with n to the sort() function.*/
    sort(people, n);

    /*Pass this array along with n to the display() function.*/
    display(people, n);
    printf("---------------------- \n");
    
    /*Pass this array along with n to the sortAnalysis() function.*/
    printf("%d\n", sortAnalysis(people, n));
    
    /*Display the number of comparisons the function returns.	Did it matter that the array was already sorted? Why? - Display your answer in comments below
    Note - this will depend on your implementation. There is not one answer*/
    printf("---------------------- \n");

    /* Bubble sort performs n comparisons on a sorted list of length n.
     * It performs a lot more comparisons on unsorted lists.
     */

    return 0;
}
