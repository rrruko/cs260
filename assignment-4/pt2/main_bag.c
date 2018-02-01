#include "listbag.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>


void assertTrue(int predicate, char *message) {
	printf("%s: ", message);
	if (predicate)
		printf("Pass \n");
	else
		printf("Fail \n");
}


int main() {

	struct list *lst = malloc(sizeof(struct list));
	initList(lst);
	printf("Initialized List \n");

	printf("---------testing addFrontList---------- \n");
	addFrontList(lst->head, 3);
	addFrontList(lst->head, 2);
	addFrontList(lst->head, 1);

	printf("displaying list: ");
	/* Should display 1, 2, 3 */
	displayList(lst->head);

	assertTrue(frontList(lst->head) == 1, "Testing head == 1 ");

	printf("---------testing addBackList---------- \n");
	addBackList(lst->head, 4);
	addBackList(lst->head, 5);

	printf("displaying list: ");
	/* Should display 1, 2, 3, 4, 5*/
    displayList(lst->head);

    assertTrue(frontList(lst->head) == 1, "Testing head == 1 ");
    assertTrue(backListRecursive(lst->head) == 5, "Testing tail == 5 ");

    printf("---------testing removeFrontList---------- \n");
    removeFrontList(lst->head);
    assertTrue(frontList(lst->head) == 2, "Testing head == 2 ");
    assertTrue(backListRecursive(lst->head) == 5, "Testing tail == 5 ");

    printf("displaying list: ");
    /* Should display 2, 3, 4, 5*/
    displayList(lst->head);

    printf("---------testing removeBackList---------- \n");
    removeBackList(lst->head);
    assertTrue(frontList(lst->head) == 2, "Testing head == 2 ");
    assertTrue(backListRecursive(lst->head) == 4, "Testing tail == 4 ");

    printf("displaying list: \n");
    /* Should display 2, 3, 4*/
    displayList(lst->head);

    printf("---------testing listContainsRecursive---------- \n");
    assertTrue(listContainsRecursive(lst->head, 3), "Testing listContainsRecursive 3");
    assertTrue(!listContainsRecursive(lst->head, 5), "Testing listContainsRecursive 5");

    printf("---------testing listRemove---------- \n");
    listRemove(lst->head, 3);

    assertTrue(!listContainsRecursive(lst->head, 3), "Testing listRemove 3");
    assertTrue(frontList(lst->head) == 2, "Testing head == 2 ");
    assertTrue(backListRecursive(lst->head) == 4, "Testing tail == 4 ");

    printf("displaying list: \n");
    /* Should display 2, 4*/
    displayList(lst->head);

    free(lst->head);

    printf("----------------- ******** testing listBag ******** ----------------- \n");

    struct bag *b = malloc(sizeof(struct list));
	initBag(b);

	printf("---------testing addToBag---------- \n");
	addToBag(b, 1);
	addToBag(b, 2);
	addToBag(b, 3);

    printf("---------testing bagContains---------- \n");
	assertTrue(bagContains(b, 3), "Testing bagContains 3");
	assertTrue(!bagContains(b, 4), "Testing bagContains 4");

    printf("---------testing isEmptyBag---------- \n");
	assertTrue(!isEmptyBag(b), "Testing isEmpty ");


	return 0;
}
