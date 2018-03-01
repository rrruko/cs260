#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define KeyType char *
#define ValueType int
#define TYPE double
#define LOAD_FACTOR_THRESHOLD .75

struct hashLink {
   KeyType key; /* The key is what you use to look up a hashLink */
   ValueType value; /* The value stored with the hashLink, an int in our case */
   struct hashLink * next; /* Notice how these are like linked list nodes */
};

struct hashMap {
    struct hashLink **table; /* Array of pointers to hashLinks */
    int tableSize; /* Number of buckets in the table */
    int count; /* Number of hash links */
    int hashID; /* ID of the hashing algorithm */
};

/* Hash functions */
int hashFunction1(char *str);
int hashFunction2(char *str);
int _hashValue(char *key, int hashNum);

/* Hash Map Functions */
void _initMap (struct hashMap * h, int tableSize, int ID);
struct hashMap *createMap (int tableSize, int ID);
void _reSizeTable(struct hashMap *h, int newCap);
void insertMap (struct hashMap * h, KeyType k, ValueType v);
int containsKey (struct hashMap * h, KeyType k);
void removeKey (struct hashMap * h, KeyType k);
ValueType valAtKey(struct hashMap *h, KeyType k);
int fullBuckets(struct hashMap *h);
int emptyBuckets(struct hashMap *h);
int linkCount(struct hashMap *h);
void printMap(struct hashMap * h);
float tableLoad(struct hashMap *h);
int capacityMap(struct hashMap *h);
void _freeMap (struct hashMap * h);
void deleteMap (struct hashMap * h);

void assertTrue(int predicate, char *message);
char* getWord(FILE *file);
void concordance(struct hashMap *ht, char *word);
