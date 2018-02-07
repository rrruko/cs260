/*
   Name: Ethan Jones
   Date: 6-2-2018
   Description: Skip lists
*/
/*
    skip list implementation
    link heights are probabilistically determined
    link heights are only allowed to exceed current max (currMax) height by one
    link heights are capped at maximum level (maxLevel)
*/

#include "skipList.h"
#include <malloc.h>

/*
    initSkipList: Skiplist is initialized
    pre: list is not null
    pre: max is at least 1 max. should be set to log n of the number of level 1
    links
    param1: list - the list
    param2: max - maximum depth of the list
    post: memory is allocated to sentinel
    maxLevel, currMax and size are initialized
*/
void initSkipList(struct skipList *list, int max) {
    assert(list != NULL);
    assert(max > 0);
    /* sentinel is an array with a pointer to every level */
    list->sentinel = malloc(sizeof(struct sLink)+sizeof(struct sLink)*max+1);
    list->maxLevel = max;/* max allowable levels */
    list->currMax = 0;/* level of highest node currently */
    list->size = 0;/* number of level 1 links */

    int i;
    for(i = max; i > 0; i--)
    {
        /* sentinel points to itself at every level */
        list->sentinel->next[i] = list->sentinel;
    }
}

/*
    levelGen: Generate a random level for new links
    pre: list is not null
    param1: list - the list
    return: random level
    post: random level cannot exceed list->maxLevel
    random level can only exceed currMax by 1
    random levels are determined by a "series of coin flips"
    Each level is 50% less common than the last
    Approximately 50% are level 2, 25% are level 3, 12.5% are level 4, etc
    Each consecutive "heads" adds one to the level, at the first "tails" we
    have reached our level
    start at level 1 and add 1 for each heads
    Ex: HHT = level 3, T = 1, THH = 1, HHHT = 4
*/
int levelGen(struct skipList *list) {
    assert(list != NULL);
    /*  here's a cute alternate way to define this procedure without
     *  looping!
     *      double r = (double)rand() / RAND_MAX;
     *      int level = 1 + (int)log2(1.0/r);
     *      return fmin(level, maxLevel);
     *  This works because a number chosen uniformly from the range (0, 1] has
     *  a 1/2^n chance of being less than 1/2^n, or, equivalently, has a 1/2^n
     *  chance that the log of its reciprocal is greater than n.
     */
    int level = 1;
    // Side-affecting loop condition!
    while (rand() % 2 == 0
        && level < list->maxLevel
        && level < list->currMax + 1) {
        level++;
    }
    return level;
}

/*
    addValTest: Adds a value to the skipList at a specified level - useful for
    testing purposes
    pre: list is not null
    pre: lvl > 0 and lvl <= maxLevel
    param1: list - the list
    param2: val - the value to add
    param3: lvl - the level of the link
    post: value is added to the skip list at each necessary level
*/
void addValTest(struct skipList *list, TYPE val, int lvl) {
    assert(list != NULL);
    assert(lvl <= list->maxLevel && lvl > 0);

    /* if lvl is greater than currMax, set currMax to lvl - this is just list
     * maintenance */
    if(lvl > list->currMax) {
        list->currMax = lvl;
    }

    /* pointers for node to insert and iterator node */
    struct sLink *insert, *curr;
    /* allocate memory for link to insert - extra space is allocated for the
     * "height" of the link */
    insert = malloc(sizeof(struct sLink) + sizeof(struct sLink)*lvl);

    /* set up node values*/
    insert->value = val;
    insert->level = lvl;

    /* initialize curr to sentinel - start at the head of the list */
    curr = list->sentinel;

    printf("inserting %d as a lvl %d node\n", val, lvl);
    int lev = list->currMax;
    while (1) {
        while (curr->next[lev] == list->sentinel
            || curr->next[lev]->value > val) {
            if (lev <= lvl) {
              struct sLink* curNext = curr->next[lev];
              curr->next[lev] = insert;
              insert->next[lev] = curNext;
            }
            if (lev > 1) {
                lev--;
            } else {
                break;
            }
        }
        if (curr->next[lev]->value == val) {
            break;
        } else {
            curr = curr->next[lev];
        }
    }
}

/*
    addVal: Adds a value to the skipList at a random level
    pre: list is not null
    pre: lvl > 0 and lvl <= maxLevel
    param1: list - the list
    param2: val - the value to add
    post: value is added to the skip list at each necessary level.
    Level is generated randomly.
    HINT - this is the same process as addValTest with one exception. You
    need to generate a level using LevelGen()
*/
void addVal(struct skipList *list, TYPE val) {
    int lev = levelGen(list);
    addValTest(list, val, lev);
}

/*
    searchVal: Searches the skipList for a value
    pre: list is not null
    param1: list - the list
    param2: val - the search value
    post: return an integer greater than 0 if found - If not found, return 0
    Returns the number of comparisons  needed to find the value if found (will
    work as boolean return)
*/
int searchVal(struct skipList *list, TYPE val) {
    int lev = list->currMax;
    int comparisons = 0;
    struct sLink* curr = list->sentinel;
    while (1) {
        comparisons++;
        while (curr->next[lev] == list->sentinel
            || curr->next[lev]->value > val) {
            if (lev > 1) {
                lev--;
            } else {
                return 0;
            }
            comparisons++;
        }
        comparisons++;
        if (curr->next[lev]->value == val) {
            return comparisons;
        } else {
            curr = curr->next[lev];
        }
    }
}

/*
    printLv: Print the specified level of the list
    pre: list is not null
    pre: lv is greater than 0 and less than list->maxLevel
    param1: list - the list
    param2: lv - level of the list to print
    post: prints all of the values at a specified level
*/
void printLv(struct skipList *list, int lv) {
    struct sLink* curr = list->sentinel;
    while (curr->next[lv] != list->sentinel) {
        printf("%d ", curr->next[lv]->value);
        curr = curr->next[lv];
    }
    printf("\n");
}

/*
    getSize: return the number of level 1 links in the skip list
    pre: list is not null
    param1: list - the list
    post: return the number of level 1 links in the list
*/
int getSize(struct skipList *list) {
    int size = 0;
    struct sLink* link = list->sentinel;
    while (link->next != NULL) {
        size++;
        link = link->next[0];
    }
    return size;
}

/*
    removeLink: Remove the first instance of the link containing the value from
    the list
    pre: list is not null
    param1: list - the list
    param2: val - value to remove
    post: link is removed from the list and pointers are adjusted
    post: if not found "Not Found" is displayed via standard output
*/
void removeLink(struct skipList *list, TYPE val) {
    /* FIX ME */



}

/*
    deleteList: delete all links from the list as well as the list
    pre: list is not null
    param1: list - the list
    post: all links are deallocated
    post: sLinks are deallocated
*/
void deleteList(struct skipList *list) {
    /* FIX ME */


}
