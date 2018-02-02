#include "listbag.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/*
    initlist: initialize the list, create the head and initialize pointers
    param: lst is the list
    pre: lst is not null
    post: none
*/
void initList (struct list *lst) {
    assert(lst != NULL);
    lst->head = malloc(sizeof(struct DLink));
    lst->head->next = NULL;
}

/*
    addFrontList: add a value to the front of the list
    param: head is the head of the list
    param: e is the value to add to the list
    pre: head is not null
    post: value is added to the front of the list
*/
void addFrontList (struct DLink *head, TYPE e) {
    assert(head != NULL);
    struct DLink* front = head->next;
    struct DLink* newFront = (struct DLink*) malloc(sizeof(struct DLink));
    struct DLink* tmp = front;
    newFront->next = tmp;
    newFront->value = e;
    head->next = newFront;
}

/*
    addBackList: add a value to the back of the list
    param: head is the front of the list
    param: e is the value to add to the list
    pre: head is not null
    post: value is added to the back of the list
*/
void addBackList(struct DLink *head, TYPE e) {
    struct DLink* elem = head;
    while (elem->next != NULL) {
        elem = elem->next;
    }
    struct DLink* last = (struct DLink*) malloc(sizeof(struct DLink));
    last->next = NULL;
    last->value = e;
    elem->next = last;
}

/*
    frontList: return the element at the head of the  list
    param: head is the front of the list
    pre: head is not null
    post: no changes to the list
    return: return value at front of the list
*/
TYPE frontList (struct DLink *head) {
    assert(head != NULL);
    return head->next->value;
}

/*
    backList: return the element in the back of the  list - MUST USE RECURSION
    param: head is the front of the list
    pre: head is not null
    post: no changes to the list
    return: return value at back of the list
*/
TYPE backListRecursive (struct DLink *head) {
    if (head->next != NULL) {
        return backListRecursive(head->next);
    } else {
        return head->value;
    }
}

/*
    removeFrontList: remove element from front of list
    param: head is the front of the list
    pre: head is not null
    post: front link is removed
*/
void removeFrontList(struct DLink *head) {
    assert(head != NULL);
    struct DLink* tmp = head->next;
    head->next = head->next->next;
    free(tmp);
}

/*
    removeBackList:    remove element from back of list
    param: head is the front of the list
    pre: head is not null
    post: back link is removed
*/
void removeBackList (struct DLink *head) {
    assert(head != NULL);
    if (head->next != NULL) {
        struct DLink* elem = head->next;
        if (elem->next == NULL) {
            head->next = NULL;
            free(elem);
        } else {
            removeBackList(elem);
        }
    }
}

/*
    displayList: print the contents of the list
    param: head is the front of the list
    pre: head is not null
    post: list contents are displayed
*/
void displayList (struct DLink *head) {
        printf("[");
    struct DLink* elem = head->next;
        while (elem != NULL) {
        printf("%d ", elem->value);
        elem = elem->next;
    }
    printf("]\n");
}

/*
    listContainsRecursive: determine whether the list contains the value - MUST USE RECURSION
    param: head is the front of the list
    param: e is the search value
    pre: head is not null
    post: no changes to the list
    return: Return 1 if found, 0 if not
 */
int listContainsRecursive (struct DLink *head, TYPE e) {
    assert(head != NULL);
    if (head->next == NULL) {
        return head->value == e;
    } else {
        return head->value == e || listContainsRecursive(head->next, e);
    }
}

/*
    listRemove: remove the first occurrence of the value from the list
    param: head is the front of the list
    param: e is the value to remove
    pre: head is not null
    pre: e is contained in the list
    post: first occurrence of e has been removed from the list
*/
void listRemove (struct DLink *head, TYPE e) {
    assert(head != NULL);
    struct DLink* elem = head;
    while (elem->next != NULL) {
        if (elem->next->value == e) {
            struct DLink* tmp = elem->next;
            elem->next = elem->next->next;
            free(tmp);
            break;
        } else {
            elem = elem->next;
        }
    }
}

/*
    isEmptyList: checks whether the list is empty or not
    param: head is the front of the list
    pre: head is not null
    post: none
    return: Return 1 if empty, 0 if not
*/
int isEmptyList(struct DLink *head) {
    assert(head != NULL);
    if(head->next == NULL) {
        return 1;
    }
    return 0;
}

/*
    freeList: Free the list
    param: head is the front of the list
    pre: head is not null
    post: each link of the list has been deallocated
*/
void freeList(struct list *lst) {
    struct DLink* head = lst->head;
    assert(head != NULL);
    struct DLink* elem = head->next;
    while (elem != NULL) {
        printf("Freeing %d\n", elem->value);
        struct DLink* nxt = elem->next;
        free(elem);
        elem = nxt;
    }
    free(head);
    free(lst);
}


/* -----------------------ListBag functions begin here---------------------- */


/*
    initBag: initialize bag
    param: b is the bag
    pre: b is not null
    post: list is allocated, size = 0
*/
void initBag(struct bag* b) {
    assert( b != NULL);
    b->lst = (struct list*)malloc(sizeof(struct list));/*Allocate for the list implementing the bag*/
    initList(b->lst);/*Initialize list*/
    b->size=0;
}

/*
    addToBag: add an element to the bag
    param: b is the bag
    param: val is the value added to the bag
    pre: b is not null
    post: val is added to the bag (list implementing the bag), size is incremented
*/
void addToBag(struct bag* b, TYPE val) {
     addFrontList(b->lst->head, val);
     b->size++;
}

/*
    removeFromBag: remove an element from the bag
    param: b is the bag
    param: val is the value to remove from the bag
    pre: b is not null
    post: Element (if found) removed from bag size is decremented.
*/
void removeFromBag(struct bag* b, TYPE val) {
    assert(b != NULL);
    if (listContainsRecursive(b->list)) {
        listRemove(b->lst->head, val);
        b->size--;
    }
}

/*
    bagContains: test if an element exists in the bag
    param: b is the bag
    param: val is the value to search for
    pre: b is not null
    post: no changes to the bag
    return: return 1 if found, otherwise return 0
*/
int bagContains(struct bag* b, TYPE val) {
    assert(b != NULL);
    return listContainsRecursive(b->lst->head, val);
}

/*
    isEmptyBag: test if the bag is empty
    param: b is the bag
    pre: b is not null
    post: no changes to the bag
    return: return 1 if found, otherwise return 0
*/
int isEmptyBag(struct bag* b) {
    assert(b != NULL);
    return isEmptyList(b->lst->head);
}

/*
    freeBag: deallocate bag memory
    param: b is the the bag
    pre: b is not null
    post: bag is deallocated
*/
void freeBag(struct bag *b) {
    assert(b != NULL);
    freeList(b->lst);
}
