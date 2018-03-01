#include "hashMap.h"

/*
    hashFunction1: The first hash function you will use - the sum of the ASCII
    values is computed param1: str - the string to hash pre: str is not NULL
    post: none
    return: the sum of the ASCII values of the word is returned
*/
int hashFunction1(char *str) {
    int sum = 0;
    int i = 0;
    for (i = 0; str[i] != '\0'; i++) {
        sum += str[i];
    }
    return sum;
}

/*
    hashFunction2: The second hash function you will use - the difference is in
    the for loop param1: str - the string to hash pre: str is not NULL post: none
    return: the hash is returned - not as easily explained as hashFunction1
*/
int hashFunction2(char *str) {
    int i;
    int h = 0;
    for (i = 0; str[i] != '\0'; i++) {
        h += (i + 1) * str[i];
    }
    return abs(h);
}

/*
    hashValue: returns the hash of the key - hash algorithm is specified
    param1: str - the string to hash
    param2: hashNum - the number of the hashing function (1 or 2 in this
    program) pre: str is not NULL post: none return: the hash is returned
*/
int _hashValue(char *key, int hashNum) {
    if (hashNum == 1) {
        return hashFunction1(key);
    } else {
        return hashFunction2(key);
    }
}

/*
    initMap: Initialize the hashMap
    param1: h - the hash map to initialize
    param2: tableSize - the size of the hash map
    pre: h is not NULL
    pre: tableSize is greater than 0
    post: memory for table has been allocated - need to store specified
    (tableSize) hash links
    post: tableSize has been set to tableSize
    post: count is set to 0
    post: hashID is set to ID
    post: all hash links (buckets) are initialized to NULL
*/
void _initMap(struct hashMap *h, int tableSize, int ID) {
    assert(h != NULL);
    assert(tableSize > 0);

    h->table = malloc(tableSize * sizeof(struct hashLink*));
    int i;
    for (i = 0; i < tableSize; i++) {
        h->table[i] = NULL;
    }
    h->tableSize = tableSize;
    h->count = 0;
    h->hashID = ID;
}

/*
    createMap: allocate memory and initialize a hash map
    param1: tableSize - the capacity of the table
    pre: tableSize > 0
    return: newly created hash map of size, tableSize
    post: memory for the hash map has been created
    post: hash map of size tableSize has been initialized
*/
struct hashMap *createMap(int tableSize, int ID) {
    assert(tableSize > 0);

    struct hashMap *h;
    h = malloc(sizeof(struct hashMap));
    assert(h != 0); /* ensure that memory was successfully allocated */

    _initMap(h, tableSize, ID);
    return h;
}

/*
    _reSizeTable: Resizes the hash map to the size, newCap. Rehashes all of the
    current keys. param1: hashMap - the map param2: newCap - the new capacity
    pre: h is not empty
    pre: newCap is > 0
    post: h now has tableSize, newCap.
    post: all keys have been re-hashed and inserted into h
    HINT - use insertMap to re-hash the keys. Everything has been completed
    except the copy/re-hash. Free the temp data as you copy/re-hash.
*/
void _reSizeTable(struct hashMap *h, int newCap) {
    struct hashLink *cur, *del;        /* Used to free the old hash links and
                                            iterate through them */
    struct hashLink **temp = h->table; /* pointer to the old table */
    int tempSize = h->tableSize;       /* size of the old table */
    _initMap(h, newCap, h->hashID);    /* Re-initialize the table */
    /* FIX ME */

    /* re-hash links */
}

/*
   insertMap: insert the key/value into a hash link - no duplicate keys are
   permitted
   param1: h - the map
   param2: k - the key to insert - in this case, the word
   param3: v - the value to insert - in this case, the number of occurrences
   pre: h is not empty
   post: map contains the key/value
   post: count has been incremented

   Duplicate values - if a duplicate key is found, leave it and insert the new
   value in the link Ex. You can't have two hash links for the word 'bobcat',
   but you can have many links in the same bucket Concordance will manage the
   word count (value) - the hash is not concerned with counts

   You must monitor the load factor and resize (double size) when the load
   factor is greater than LOAD_FACTOR_THRESHOLD (.75) Use the tableLoad function
   - contains an explanation of load factor
*/
void insertMap(struct hashMap *h, KeyType k, ValueType v) {
    /* hash the key */
    int hash = _hashValue(k, h->hashID);
    hash = hash % h->tableSize;

    // debugging information
    printf("KEY: %s HASH: %d val:%d \n", k, hash, v);

    struct hashLink* link = h->table[hash];
    if (link == NULL) {
        h->table[hash] = malloc(sizeof(struct hashLink));
        link = h->table[hash];
        link->next  = NULL;
        link->key   = k;
        link->value = v;
        h->count += 1;
    } else {
        while (strcmp(link->key, k) != 0 && link->next != NULL) {
            link = link->next;
        }
        if (strcmp(link->key, k) == 0) {
            printf("  [That key was already present.]\n");
            link->value = v;
        } else {
            link->next = malloc(sizeof(struct hashLink));
            link->next->next  = NULL;
            link->next->key   = k;
            link->next->value = v;
            h->count += 1;
        }
    }

    if (tableLoad(h) > LOAD_FACTOR_THRESHOLD) {
        _reSizeTable(h, h->tableSize * 2);
    }
}

/*
    containsKey: determines whether the key is contained in the map
    param1: h - the map
    param2: k - the key to search for
    pre: h is not null
    post: none
    return: return 0 is not found, otherwise return 1
*/
int containsKey(struct hashMap *h, KeyType k) {
    assert(h != NULL);
    int hash = _hashValue(k, h->hashID);
    hash %= h->tableSize;

    struct hashLink* link = h->table[hash];
    if (link != NULL) {
        printf("There's something here...\n");
        while (strcmp(link->key, k) != 0 && link->next != NULL) {
            printf("Stepping...\n");
            link = link->next;
        }
        if (strcmp(link->key, k) == 0) {
            return 1;
        }
    }

    return 0;
}

/*
    removeKey: find the hash link for the key and remove it, also free the
    memory for the hash link If unable to find the key, then print an
    appropriate message
    param1: h - the map
    param2: k - the key to remove
    pre: h is not NULL
    post: key has been removed from the table
    post: count has been decremented
    HINT - When the value is the first link, then it is a special case
 */
void removeKey(struct hashMap *h, KeyType k) {
    assert(h != NULL);
    int hash = _hashValue(k, h->hashID);
    hash %= h->tableSize;

    struct hashLink** link = &(h->table[hash]);
    while (*link != NULL) {
        if (strcmp((*link)->key, k) == 0) {
            struct hashLink* tmp = *link;
            *link = (*link)->next;
            free(tmp);
        } else {
            link = &((*link)->next);
        }
    }
}

/*
    valAtKey: return the value stored at the key
    param1: h - the map
    param2: k - the key to search for
    pre: h is not null
    pre: if key not found, then display an appropriate message
    post: none
    return: return the value found at the key - return 0 if not found
*/
ValueType valAtKey(struct hashMap *h, KeyType k) {
    assert(h != NULL);
    int hash = _hashValue(k, h->hashID);
    hash %= h->tableSize;
    struct hashLink* link = h->table[hash];
    if (link == NULL) {
        printf("???");
    }
    while (link != NULL) {
        if (strcmp(link->key, k) == 0) {
            return link->value;
        }
        link = link->next;
    }
    printf("Key not found\n");
    return 0;
}

/*
    sizeMap: returns the number of hashLinks in the map
    param1: h - the map
    pre: h is not NULL
    post: none
    return: the bucketCount of the hash table
    this will be the number of 'chains' in the table
*/
int fullBuckets(struct hashMap *h) {
    assert(h != NULL);
    int count = 0;
    int i;
    for (i = 0; i < h->tableSize; i++) {
        if (h->table[i] != NULL) {
            count += 1;
        }
    }
    return count;
}

/*
    emptyBuckets: returns the number of empty buckets in the table, these are
    buckets which have no hashlinks in them
    param1: h - the hash table
    pre: h is not null
    post: no changes to the table
    return: the number of empty buckets in the table
    HINT - you need to check the hash map for NULLs
*/
int emptyBuckets(struct hashMap *h) {
    assert(h != NULL);
    return h->tableSize - fullBuckets(h);
}

/*
    linkCount: returns the number of hashLinks in the map
    param1: h - the map
    pre: h is not NULL
    post: none
    return: the count of the hash table
    this will be the total number of hash links in the table
*/
int linkCount(struct hashMap *h) {
    assert(h != NULL);
    int count = 0;
    int i;
    for (i = 0; i < h->tableSize; i++) {
        struct hashLink* link = h->table[i];
        while (link != NULL) {
            link = link->next;
            count += 1;
        }
    }
    return count;
}

/*
    printMap: prints the contents of the hash map
    param1: h - the map
    pre: h is not NULL
    post: map has been printed to standard output
    return: contents of the hash map are displayed via standard output - see
    format below
    bucket x: key (value), key (value, ....
    Ex. Bucket 1: cat (1), dog (1), the (5)...
*/
void printMap(struct hashMap *h) {
    assert(h != NULL);
    int i;
    for (i = 0; i < h->tableSize; i++) {
        printf("Bucket %d: ", i);
        struct hashLink* link = h->table[i];
        while (link != NULL) {
            printf("%s (%d)", link->key, link->value);
            link = link->next;
            if (link != NULL) {
                printf(", ");
            }
        }
        printf("\n");
    }
}

/*
    tableLoad: determine the load of the table
    there are a couple ways you can calculate this - we want full buckets /
    empty buckets we are not concerned with the number of hash links - we are
    assuming a reasonable hash param1: h - the hash table pre: h is not null
    post: no changes to the table
    return: returns the ratio of: full buckets / table size
    HINT - cast one of the operands to a float, otherwise you have integer
    division
*/
float tableLoad(struct hashMap *h) {
    /* FIX ME */

    return 0;
}

/*
    capacityMap: returns the number of buckets in the map
    param1: h - the hash map
    pre: - h is not null
    post: no changes to the map
    return: return the tableSize
*/
int capacityMap(struct hashMap *h) {
    /* FIX ME */

    return 0;
}

/*
    freeMap: free all memory used by the buckets
    param1: h - the hash map
    pre: - h is not null
    post: memory used by the hash buckets has been freed
*/
void _freeMap(struct hashMap *h) { /* FIX ME */ }

/*
    freeMap: deallocate buckets and the hash map
    param1: h - the hash map
    pre: - h is not null
    post: memory used by the hash buckets and the hash table has been freed
*/
void deleteMap(struct hashMap *h) {
    assert(h != NULL);

    _freeMap(h); /* free all memory used by the buckets */
    free(h);     /* free the hash map */
}
