#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "dynamicArray.h"

/*
    compare: compare two tasks by priority
    param: left - first task
    param: right - second task
    pre: none
    post: none
    return: return scheme is below
        -1 if priority of left < priority of right
        1 if priority of left > priority of right
        0 if priority of left = priority of right
*/
int compare(TYPE left, TYPE right) {
    if (left.priority < right.priority)
        return -1;
    else if (left.priority > right.priority)
        return 1;
    else
        return 0;
}

/*
    initDynArr: Initialize (including allocation of data array) dynamic array.
    param1: d - pointer to the dynamic array
    param2 : capacity - capacity of the dynamic array
    pre: d is not null
    post: internal data array can hold cap elements
    post: d->data is not null
*/
void initDynArr(struct DynArr *d, int capacity) {
    assert(capacity > 0);
    assert(d != NULL);
    d->data = (TYPE *) malloc(sizeof(TYPE) * capacity);
    assert(d->data != NULL);
    d->size = 0;
    d->capacity = capacity;
}

/*
    createDynArr: Allocate and initialize dynamic array.
    param: cap desired capacity for the dynamic array
    pre: cap is greater than 0
    post: none
    ret: a non-null pointer to a dynArr of cap capacity and 0 elements in it.
*/
struct DynArr *createDynArr(int cap) {
    assert(cap > 0);
    struct DynArr *dyn;
    dyn = malloc(sizeof(struct DynArr));
    if(!dyn) {
        printf("Failed to allocate memory \n");
    }
    initDynArr(dyn,cap);
    return dyn;
}

/*
    freeDynArr: Deallocate data array in dynamic array.
    param: d - pointer to the dynamic array
    pre: none
    post: d->data points to null
    post: size and capacity are 0
    post: the memory used by d->data is freed
*/
void freeDynArr(struct DynArr *d) {
    if(d->data != NULL) {
        free(d->data); /* free the space on the heap */
        d->data = NULL; /* make it point to null */
    }
    d->size = 0;
    d->capacity = 0;
}

/*
    deleteDynArr: Deallocate data array and the dynamic array.
    param: d - pointer to the dynamic array
    pre: d is not NULL
    post: the memory used by d->data is freed
    post: the memory used by d is freed
*/
void deleteDynArr(struct DynArr *d) {
    assert(d != NULL);
    freeDynArr(d);
    free(d);
}

/*
    sizeDynArr: Get the size of the dynamic array
    param: d - pointer to the dynamic array
    pre: d is not null
    post: none
    ret: the size of the dynamic array
*/
int sizeDynArr(struct DynArr *d) {
    assert(d != NULL);
    return d->size;
}

/*
    getDynArr: Get an element from the dynamic array from a specified position
    param1: d - pointer to the dynamic array
    param2: pos - integer index to get the element from
    pre: d is not null
    pre: d is not empty
    pre: pos <= size of the dynamic array and >= 0
    post: no changes to the dynamic array
    return: value stored at index position, pos
*/
TYPE getDynArr(struct DynArr *d, int pos) {
    assert(d != NULL);
    assert(pos <= d->size);
    assert(pos >= 0);

    return d->data[pos];
}

/*
    _dynArrSetCapacity: Resizes the old array to the size of capacity
    param1: d - pointer to the dynamic array
    param2: newCap - the new desired capacity
    pre: d is not null
    post: d has capacity newCap
*/
void _dynArrSetCapacity(struct DynArr *d, int newCap) {
    /* Create a new dynamic array with new capacity */
    TYPE *newArr = malloc(sizeof(TYPE)*newCap);
    assert(newArr != NULL);

    int i;
    for(i = 0; i < d->size; i++){
        newArr[i] = d->data[i];
    }

    free(d);
    d->data = newArr;
    d->capacity = newCap;
    d->size = i;

}

/*
    addDynArr: Adds an element to the end of the dynamic array
    param: d - pointer to the dynamic array
    param: val - the value to add to the end of the dynamic array
    pre: the dynArry is not null
    post: size increases by 1
    post: if reached capacity, capacity is doubled
    post: val is in the last utilized position in the array
*/
void addDynArr(struct DynArr *d, TYPE val) {
    assert(d != NULL);
    /* If full, then re-size */
    if(d->size >= d->capacity) {
        _dynArrSetCapacity(d, d->capacity * 2);
    }
    d->data[d->size] = val;
    d->size++;
}

/*
    putDynArr: Put an item into the dynamic array at the specified location, overwriting the element that was there
    param1: d - pointer to the dynamic array
    param2: pos - the index to put the value into
    param3: val    - the value to insert
    pre: d is not null
    pre: d is not empty
    pre: pos >= 0 and pos < capacity of the array
    post: index (pos) contains new value (val)
*/
void putDynArr(struct DynArr *d, int pos, TYPE val) {
    assert(d != NULL);
    assert(pos >= 0);
    assert(pos < d->capacity);

    d->data[pos] = val;

}

/*
    swapDynArr: Swap two specified elements in the dynamic array
    param1: d - pointer to the dynamic array
    param2: i - one of the elements to be swapped
    param3: j - one of the elements to be swapped
    pre: d is not null
    pre: d is not empty
    pre: i & j are greater than or equal to 0
    pre: i & j are less or equal to the size of the dynamic array
    post: index i now holds the value at j and index j now holds the value at i
*/
void swapDynArr(struct DynArr *d, int i, int  j) {
    TYPE  temp;
    assert(d != NULL);
    assert(i <= d->size);
    assert(j <= d->size);
    assert(i >= 0);
    assert(j >= 0);

    temp = d->data[i];
    d->data[i] = d->data[j];
    d->data[j] = temp;
}

/*
    removeAtDynArr: Remove the element at the specified location from the array, shifts other elements back one to fill the gap
    param1: d - pointer to the dynamic array
    param2: pos - location of element to remove
    pre: d is not null
    pre: d is not empty
    pre: pos < size and pos >= 0
    post: the element at pos is removed
    post: the elements past pos are shifted back one
*/
void removeAtDynArr(struct DynArr *d, int idx) {
    int i;
    assert(d != NULL);
    assert(idx < d->size);
    assert(idx >= 0);

   /* Shift all elements up */
   for(i = idx; i < d->size-1; i++){
      d->data[i] = d->data[i+1];
   }
   d->size--;
}

/*
    isEmptyDynArr: returns boolean based on whether the array is empty
    param: d - pointer to the dynamic array
    pre: d is not null
    post: none
    ret: 1 if empty, otherwise return 0
*/
int isEmptyDynArr(struct DynArr *d) {
    assert(d != NULL);

    if(d->size == 0) {
        return 1;
    }
    return 0;
}

/*
    copyDynArr: copy elements from a dynamic array to another dynamic array
    param1: source - pointer to the source dynamic array
    param2: destination - pointer to the destination dynamic array
    pre: source is not null and s is not empty
    post: destination is initialized
    post: the elements from source are copied to destination
*/
void copyDynArr(struct DynArr *source, struct DynArr *destination) {
    assert(source != NULL);
    assert(source->size > 0);

    initDynArr(destination, source->capacity);

    int i;
    for(i = 0; i < source->size; i++) {
        destination->data[i] = source->data[i];/* copy elements to destination array */
    }

    destination->size = source->size;
}

/*
    Heap-based priority queue implementation ----------------------------------- Starts here --------------------------------------
*/

/*
    getMinHeap: Get the first node in the heap (root)
    param: heap - pointer to the heap
    pre: heap is not empty
    post: no changes to the heap
    return: value of first node's value
*/
TYPE getMinHeap(struct DynArr *heap) {
    return getDynArr(heap, 0);
}


/*
    _smallerIndexHeap: Get the index of the smaller node between two nodes in a heap - this is an auxiliary function
    param1: heap - pointer to the heap
    param2: i - index of one node
    param3: j - index of the other node
    pre: i < size and j < size
    return: the index of the smaller node
*/
int _smallerIndexHeap(struct DynArr *heap, int i, int j) {
    assert(i < heap->size && j < heap->size);
    /* Don't actually need to be left and right */
    TYPE leftChild = heap->data[i];
    TYPE rightChild = heap->data[j];
    return compare(leftChild, rightChild) == -1 ? i : j;
}

/*
    getParentIndex: Get the index of the parent of the node at the given index
    (helper for _siftUp)
*/
int getParentIndex(int i) {
    return (i - 1) / 2;
}

/*
    _siftUp: Compare index to it's parent and swap it up the heap until it is in place
    param1: heap - pointer to the heap
    param2: index - the index of the child node (to be swapped)
    pre: heap is not null
    pre: index < heap->size
    post: heap properties are maintained
*/
void _siftUp(struct DynArr *heap, int index) {
    assert(index < heap->size);
    while(index > 0) {
        int parentIndex = getParentIndex(index);
        int order = compare(heap->data[parentIndex], heap->data[index]);
        if (order == 1) {
            /* The parent is greater than the child, so they're out of order */
            /* printf("  swapped %d and %d\n", parentIndex, i); */
            swapDynArr(heap, parentIndex, index);
            index = getParentIndex(index);
        } else {
            return;
        }
    }
}

/*
    getLeftChildIx: Get the index of the left child of the node at the given
    index (helper for _siftDown)
*/
int getLeftChildIx(int i) {
    return i * 2 + 1;
}

/*
    getRightChildIx: Get the index of the right child of the node at the given
    index (helper for _siftDown)
*/
int getRightChildIx(int i) {
    return i * 2 + 2;
}

/*
    _siftDown: Compare index to it's children and swap with the smaller element
    param1: heap - pointer to the heap
    param2: index - the index of the parent node (to be swapped)
    pre: heap is not null
    pre: index < floor((heap->size-1)/2)
    post: heap properties are maintained
*/
void _siftDown(struct DynArr *heap, int index) {
    while (1) {
        int lChildIx = getLeftChildIx(index);
        int rChildIx = getRightChildIx(index);

        /* If there are two children: */
        if (lChildIx < heap->size && rChildIx < heap->size) {
                int smallerIx = _smallerIndexHeap(heap, lChildIx, rChildIx);
                swapDynArr(heap, smallerIx, index);
                index = smallerIx;
        }
        /* If the left child is smaller: */
        else if (lChildIx < heap->size &&
                compare(heap->data[lChildIx], heap->data[index]) == -1) {
            swapDynArr(heap, lChildIx, index);
            index = lChildIx;
        } 
        /* If the right child is smaller: */
        else if (rChildIx < heap->size &&
                compare(heap->data[rChildIx], heap->data[index]) == -1) {
            swapDynArr(heap, rChildIx, index);
            index = rChildIx;
        } 
        /* If there are no smaller children, we're done */
        else {
            return;
        }
    }
}

/*
    addHeap: Add a node to the heap in last position - call siftUp() to get the node in place
    param1: heap - pointer to the heap
    param2: val - node to be added to the heap
    pre: heap is not null
    post: node is added to the heap (maintain heap properties)
    post: heap size is incremented
*/
void addHeap(struct DynArr *heap, TYPE val) {
    addDynArr(heap, val);
    /* printf("Added (%d,%s)\n", val.priority, val.description); */
    _siftUp(heap, heap->size - 1);
}

/*
    removeMinHeap: Remove the first node from the heap -  call siftDown() to get the node in place
    param: heap - pointer to the heap
    pre: heap is not empty
    post: the first node is removed from the heap, the last node is promoted to root - use siftDown() to maintain the heap
    HINT: use the _smallerIndexHeap to find the smaller node of the current node
*/
void removeMinHeap(struct DynArr *heap) {
    assert(heap->size > 0);
    TYPE last = heap->data[heap->size - 1];
    heap->data[0] = last;
    heap->size--;
    _siftDown(heap, 0);
}
