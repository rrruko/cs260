/*	dynamicArray.c: Dynamic Array implementation */
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "dynamicArray.h"

#define bool int
#define true 1
#define false 0

struct DynArr {
	TYPE *data;		/* pointer to the data array */
	int size;		/* Number of elements in the array */
	int capacity;	/* capacity of the array */
};

/* ------------------Dynamic Array Functions--------------------- */

/* 	initDynArr: initialize (including allocation of data array) dynamic array
	param: d is the pointer to the dynamic array
	param: cap is the capacity of the dynamic array
	pre: d is not null
	pre: capacity is greater than 0
	post: internal data array can hold capacity elements
	post: d->data has been allocated memory
*/
void initDynArr(DynArr *d, int capacity) {
	assert(capacity > 0);
	assert(d!= 0);
	d->data = (TYPE *) malloc(sizeof(TYPE) * capacity);
	assert(d->data != 0);
	d->size = 0;
	d->capacity = capacity;
}

/* 	createDynArr: allocate and initialize dynamic array
	param: cap is the desired capacity for the dynamic array
	pre: none
	post: none
	ret: a non-null pointer to a dynArr of cap capacity and 0 elements in it
*/
DynArr* createDynArr(int cap) {
	DynArr *dyn;
	assert(cap > 0);
	dyn = (DynArr *)malloc(sizeof( DynArr));
	if(!dyn) {
		printf("Failed to allocate memory \n");
	}
	initDynArr(dyn,cap);
	return dyn;
}

/* 	freeDynArr: deallocate data array in dynamic array
	param: d is the pointer to the dynamic array
	pre: none
	post: d->data points to null
	post: size and capacity are 0
	post: the memory used by d->data is freed
*/
void freeDynArr(DynArr *d) {
	if(d->data != 0) {
		free(d->data); 	/* free the space on the heap */
		d->data = 0;   	/* make it point to null */
	}
	d->size = 0;
	d->capacity = 0;
}

/* 	deleteDynArr: deallocate memory from the array
	param: d is the pointer to the dynamic array
	pre: none
	post: the memory used by d->data is freed
	post: the memory used by d is freed
*/
void deleteDynArr(DynArr *d) {
	freeDynArr(d);
	free(d);
}

/* 	sizeDynArr: get the size of the dynamic array
	param: d is the pointer to the dynamic array
	pre: d is not null
	post: none
	ret: the size of the dynamic array
*/
int sizeDynArr(DynArr *d) {
    assert(d != 0);
	return d->size;
}

/* 	addDynArr: adds an element to the end of the dynamic array
	param: d is the pointer to the dynamic array
	param: val is the value to add to the end of the dynamic array
	pre: the dynArry is not null
	post: size increases by 1
	post: if reached capacity, capacity is doubled
	post: val is in the last utilized position in the array
*/
void addDynArr(DynArr *d, TYPE val) {
	/* FIXME: You will write this function */
	if (d == NULL) {
	    return;
	}
        if (d->size == d->capacity) {
	    DynArr* new = createDynArr(d->capacity * 2 + 1);
            int i;
	    for (i = 0; i < d->size; i++) {
                addDynArr(new, d->data[i]);
            }
            addDynArr(new, val);
            free(d->data);
            d->data = new->data;
            d->size = new->size;
            d->capacity = new->capacity;
	} else {
	    d->data[d->size] = val;
            d->size += 1;
        }
        printf("new size is %d, new cap is %d\n", d->size, d->capacity);
}

/*	getDynArr: get an element from the dynamic array from a specified position
	param: d is the pointer to the dynamic array
	param: pos is the index position to get the element from
	pre: d is not null
	pre: d is not empty
	pre: 0 <= pos <= size of the dyn array
	post: no changes to the dyn Array
	ret: value stored at index pos
*/
TYPE getDynArr(DynArr *d, int pos) {
	return d->data[pos];
}

/*	putDynArr: put an item into the dynamic array at the specified location, overwriting the element that was there
	param: d is the pointer to the dynamic array
	param: pos is the index position where val will be inserted
	param: val the value to insert
	pre: d is not null
	pre: d is not empty
	pre: pos >= 0 and pos < size of the array
	post: index pos contains new value, val
*/
void putDynArr(DynArr *d, int pos, TYPE val) {
	d->data[pos] = val;
}

/*	swapDynArr: swap two specified elements in the dynamic array
	param: d is the pointer to the dynamic array
	param: i, j are the elements to be swapped
	pre: d is not null
	pre: d is not empty
	pre: i & j are greater than or equal to 0
	pre: i & j are less than the size of the dynamic array
	post: index i now holds the value at j and index j now holds the value at i
*/
void swapDynArr(DynArr *d, int i, int j) {
	/* FIXME: You will write this function */
        TYPE tmp = d->data[i];
        d->data[i] = d->data[j];
        d->data[j] = tmp;
}

/*	removeAtDynArr: remove the element at the specified location from the array, shifts other elements back one to fill the gap
	param: d is the pointer to the dynamic array
	param: pos is the location of element to remove
	pre: d is not null
	pre: d is not empty
	pre: pos <= size and pos >= 0
	post: the element at pos is removed
	post: the elements past pos are shifted back
	post: size is decremented
*/
void removeAtDynArr(DynArr *d, int pos) {
        if (d == NULL || d->size == 0
            || pos < 0 || pos >= d->size) {
            return;
        } 
        int i;
        for (i = 0; i < d->size - 1; i++) {
            if (i >= pos) {
                d->data[i] = d->data[i + 1];
            }
        }
	d->size -= 1;
}

/* ------------------Stack Interface Functions---------------------- */

/*	isEmptyDynArr: determines whether the stack has anything on it (encoded in an int)
	param: d pointer to the dynamic array
	pre: the dynamic array is not null
	post: none
	ret: 1 if empty, otherwise 0
*/
int isEmptyDynArr(DynArr *d) {
	return d->size == 0 ? 1 : 0;	
}

/* 	pushDynArr: push an element onto the top of the stack
	param: d pointer to the dynamic array
	param: val the value to push onto the stack
	pre: d is not null
	post: size increases by 1 - if capacity is reached, then capacity is doubled
	post: val is on the top of the stack
*/
void pushDynArr(DynArr *d, TYPE val) {
	addDynArr(d, val);
}


/* 	popDynArr: removes the element on top of the stack
	param: d pointer to the dynamic array
	pre: d is not null
	pre: d is not empty
	post: size is decremented by 1
	Post: the top has been removed
*/
void popDynArr(DynArr *d) {
	removeAtDynArr(d, d->size - 1);
}

/*	peekDynArr: returns the element at the top of the stack
	param: d pointer to the dynamic array
	pre: d is not null
	pre: d is not empty
	post: no changes to the stack
*/
TYPE peekDynArr(DynArr *d) {
        return d->data[d->size - 1];
}

/* ------------------Bag Interface Functions------------------ */

/*	containsDynArr: determines whether the bag has anything on it (encoded in an int)
	param: d pointer to the dynamic array
	param: val the value to look for in the bag
	pre: d is not null
	pre: d is not empty
	post: if true, 1 is returned
	post: if false, 0 is returned
	post: no changes to the bag
*/
int containsDynArr(DynArr *d, TYPE val) {
	/* FIXME: You will write this function */
        if (d == NULL || d->size == 0) {
            return false;
        }
        bool contains = false;
        int i;
	for (i = 0; i < d->size; i++) {
	    contains |= d->data[i] == val;
	}
        
	/* FIXME:  You will change this return value */
        return contains;
}

/*	removeDynArr: removes the first occurrence of the specified value from the collection (if it occurs)
	param: d pointer to the dynamic array
	param: val the value to remove from the array
	pre: d is not null
	pre: d is not empty
	post: val has been removed
	post: size of the bag is reduced by 1
*/
void removeDynArr(DynArr *d, TYPE val) {
	/* FIXME: You will write this function */
        if (d == NULL || d->size == 0) {
            return;
        } 

        int i;
        bool removed = false;
        for (i = 0; i < d->size - 1; i++) {
            removed |= d->data[i] == val;
            if (removed) {
                d->data[i] = d->data[i + 1];
            }
        }
        if (removed) {
            d->size -= 1;
        }
}
