/* CS260 - Assignment 1 - EX 3*/
/* Name: Ethan Jones
 * Date: 9-1-2018
 * Solution description: Extra more pointer stuff
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define COUNT 10

/*Sex: (M)ale or (F)email*/
struct person {
    int age;
    char sex;
};

struct person* allocate();
void generate(struct person* people);
void output(struct person* people);
void stats(struct person* people);
void deallocate(struct person* people);


int main() {
    srand(time(NULL));

    struct person* people = NULL;

    /*call allocate
	set people to the pointer returned by the function call*/
    people = allocate();

    /*call generate*/
    generate(people);

    /*call output*/
    output(people);

    /*call stats*/
    stats(people);

    /*call deallocate*/
    deallocate(people);

    return 0;
}

struct person* allocate() {
    /*Allocate memory for ten persons - use malloc*/
    struct person* ten_persons = (struct person*) malloc(COUNT * sizeof(struct person));

    /*return the pointer*/
    return ten_persons;
}

void generate(struct person* people) {
    /*Generate random age and sex for 10 persons and store in people
	Age is between 18 and 90 - sex is either M or F
	Calculate random numbers between using rand().
	Simply assigning ages 19, 20, 21.. is not sufficient*/
    int i;
    for (i = 0; i < COUNT; i++) {
        people[i].age = rand() % (90 - 18) + 18;
        people[i].sex = rand() % 2 == 0 ? 'M' : 'F';
    }
}

void output(struct person* people) {
    /*Output information about the ten persons in the format:
	Person 1: Age: varAge Sex: varSex
	...
	Person 10: Age: varAge Sex: varSex*/
    int i;
    for (i = 0; i < COUNT; i++) {
        printf("Person %d: Age: %d Sex: %c\n", i + 1, people[i].age, people[i].sex);
    }
}

void stats(struct person* people) {
    /*Compute and print the minimum, maximum and average age of the ten persons*/
    int min = people[0].age;
    int max = people[0].age;
    float avg = 0;
    int i;
    for (i = 0; i < COUNT; i++) {
        int age = people[i].age;
        min = age < min ? age : min;
        max = age > max ? age : max;
        avg += age;
    }
    avg /= COUNT;
    printf("min: %d\n", min);
    printf("max: %d\n", max);
    printf("avg: %f\n", avg);
}

void deallocate(struct person* people) {
    /*Deallocate memory from people by calling free()*/
    free(people);
}
