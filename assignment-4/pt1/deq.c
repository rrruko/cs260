#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deq.h"

/*
	initDeque: Initialize deque
	param: q is the pointer to the deque
	pre: q is not null
	post: q->Sentinel is allocated memory and q->size equals zero
	Sentinel points to the head and tail of the list
*/
void initDeque (struct Deque *q) {
	q->Sentinel = malloc(sizeof(struct DLink));
	q->Sentinel->next = q->Sentinel;
	q->Sentinel->prev = q->Sentinel;
	q->size = 0;
}

/*
	addBackDeque: Adds a link to the back (tail) of the deque
	param: q is the pointer to the deque
	param: val is the value to be added
	pre: q is not null
	post: a link storing val is added to the back of the deque
*/
void addBackDeque (struct Deque *q, TYPE val) {
	/* FIX ME*/
	
	
}

/*
	addFrontDeque: adds a link to the front (head) of the deque
	param: q is the pointer to the deque
	param: val is the value to be added
	pre: q is not null
	post: a link storing val is added to the front of the deque
*/
void addFrontDeque(struct Deque *q, TYPE val) {
	/* FIX ME*/
	
	
}

/*
	isEmptyDeque: check whether the deque is empty
	param: q is the pointer to the deque
	pre: q is not null
	ret: 1 if the deque is empty. Otherwise, 0.
*/
int isEmptyDeque(struct Deque *q) {
	/* FIX ME*/
	
	return 0;
}

/*
	frontDeque: get the value of the front of the deque
	param: q is the pointer to the deque
	pre: q is not null and q is not empty
	post: none
	ret: value of the front of the deque
*/
TYPE frontDeque(struct Deque *q) {
	/* FIX ME*/
	
	return 0;
}

/*
	backDeque: get the value of the back of the deque
	param: q is the pointer to the deque
	pre: q is not null and q is not empty
	post: none
	ret: value of the back of the deque
*/
TYPE backDeque(struct Deque *q) {
	/* FIX ME*/
	
	return 0;
}

/*
	printDeque: print the links in the deque from front to back
	param: q is the pointer to the deque
	pre: q is not null and q is not empty
	post: the links in the deque are printed from front to back
*/
void printDeque(struct Deque *q) {
	/* FIX ME*/
	
	
}

/*
	removeFrontDeque: remove the front of the deque
	param: q is the pointer to the deque
	pre: q is not null and q is not empty
	post: the front is removed from the deque
*/
void removeFrontDeque (struct Deque *q) {
	/* FIX ME*/
	
	
}


/*
	removeBackDeque: remove the back of the deque
	param: q is the pointer to the deque
	pre: q is not null and q is not empty
	post: the back is removed from the deque
*/
void removeBackDeque(struct Deque *q) {
	/* FIX ME*/
	
	
}


/*
	freeDeque: de-allocate all links of the deque
	param: q is the pointer to the deque
	pre: none
	post: all links (including backSentinel) are de-allocated
*/
void freeDeque(struct Deque *q) {
	/* FIX ME*/
	
}
