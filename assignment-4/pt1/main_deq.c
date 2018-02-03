#include <stdio.h>
#include <stdlib.h>
#include "deq.h"

void assertTrue(int predicate, char *message) {
    printf("%s: ", message);
    if (predicate) {
        printf("Pass \n");
    } else {
        printf("Fail \n");
    }
}

int main () {
    struct Deque *testDeque;
    testDeque = malloc(sizeof(struct Deque));

    printf("Testing Deque ADT based on Circularly-Doubly-Linked List \n");
    /*Initialize the deque */
    initDeque(testDeque);

    /*Testing isEmpty */
    printf("-----------Testing isEmptyDeque -----------\n");
    assertTrue(isEmptyDeque(testDeque) == 1, "Testing isEmptyDeque");

    printf("-----------Testing addBackDeque-----------\n");
    /*Add 3 to the back */
    printf("Adding 3 to back\n");
    addBackDeque(testDeque, 3);
    /*Add 4 to the back */
    printf("Adding 4 to back\n");
    addBackDeque(testDeque, 4);
    /*Add 5 to the back */
    printf("Adding 5 to back\n");
    addBackDeque(testDeque, 5);

    /*Should print 3.0  4.0  5.0 */
    printf("-----------Testing printDeque-----------\n");
    printDeque(testDeque);
    assertTrue(frontDeque(testDeque) == 3, "Testing front == 3 ");
    assertTrue(backDeque(testDeque) == 5, "Testing back == 5 ");

    printf("-----------Testing addFrontDeque-----------\n");
    /*Add 2 to the front */
    printf("Adding 2\n");
    addFrontDeque(testDeque, 2);
    /*Add 1 to the front */
    printf("Adding 1\n");
    addFrontDeque(testDeque, 1);

    /*Should print 1, 2, 3, 4, 5 */
    printf("-----------Testing printDeque-----------\n");
    printDeque(testDeque);
    assertTrue(frontDeque(testDeque) == 1, "Testing front == 1 ");
    assertTrue(backDeque(testDeque) == 5, "Testing back == 5 ");

    printf("-----------Testing frontDeque AND backDeque -----------\n");
    assertTrue(frontDeque(testDeque) == 1, "Testing front == 1 ");
    assertTrue(backDeque(testDeque) == 5, "Testing back == 5 ");

    /*Remove the back of the deque */
    printf("-----------Testing removeFrontDeque -----------\n");
    removeFrontDeque(testDeque);
    assertTrue(frontDeque(testDeque) == 2, "Testing front == 2 ");
    /*Should print: 2, 3, 4, 5 */
    printDeque(testDeque);

    /*Remove the front of the deque */
    printf("-----------Testing removeBackDeque -----------\n");
    removeBackDeque(testDeque);
    assertTrue(backDeque(testDeque) == 4, "Testing back == 4 ");
    /*Should print: 2, 3, 4 */
    printDeque(testDeque);

    /*Testing isEmpty */
    printf("-----------Testing isEmptyDeque -----------\n");
    assertTrue(!isEmptyDeque(testDeque), "Testing !isEmptyDeque");

    printf("Removing 3 elements from testDeque\n");
    removeBackDeque(testDeque);
    removeBackDeque(testDeque);
    removeBackDeque(testDeque);

    assertTrue(isEmptyDeque(testDeque), "Testing isEmptyDeque");

    addBackDeque(testDeque, 9);
    freeDeque(testDeque);

    return EXIT_SUCCESS;
}
