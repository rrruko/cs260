#include "hashMap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    assertTrue: testing function
    param1: predicate - result of the test function
    param2: message - the output message
    pre: none
    post: none
*/
void assertTrue(int predicate, char *message) {
    printf("%s: ", message);
    if (predicate)
        printf("Pass \n");
    else
        printf("Fail \n");
}

/*
    getWord: function takes a FILE pointer and returns a string which is the next
    word in the file words are defined to be characters, apostrophes or numbers
    separated by periods, spaces or newlines param1: file - the file to parse
    pre: none
    post: no changes to the file
    return: current word of file is returned. NULL is returned at the end of the
    file
*/
char *getWord(FILE *file) {
    int length = 0;
    int maxLength = 16;
    char character;

    char *word = malloc(sizeof(char) * maxLength);
    assert(word != NULL);

    while ((character = fgetc(file)) != EOF) {
        if ((length + 1) > maxLength) {
            maxLength *= 2;
            word = (char *)realloc(word, maxLength);
        }
        if ((character >= '0' && character <= '9') ||
            (character >= 'A' && character <= 'Z') ||
            (character >= 'a' && character <= 'z') || character == 39) {
            word[length] = character;
            length++;
        } else if (length > 0) {
            break;
        }
    }

    if (length == 0) {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/*
    concordance: create a hash map which contains word frequencies
    param1: ht - the hash map
    param2: word - the current word to hash
    pre: ht is not NULL
    post: key and value is now updated
    if the key already exists, add 1 to the value
    HINT - this is a 'normal' insert, the difference is that the value is not
    always 1 use valAtKey() and insertMap()
*/
void concordance(struct hashMap *ht, char *word) {
    assert(ht != NULL);
    int v = valAtKey(ht, word);
    printf("valAtKey(ht, %s) is %d\n", word, v);
    insertMap(ht, word, v + 1);
}

int main(int argc, const char *argv[]) {
    char *fn; /* File name */
    struct hashMap *hashTable, *hashTable2;
    FILE *filePtr;

    fn = "text1.txt"; /* the file name and path */
    printf("Opening file: %s \n", fn);
    filePtr = fopen(fn, "r");
    hashTable = createMap(40, 1);

    char *word;
    while ((word = getWord(filePtr)) != '\0') {
        insertMap(hashTable, word, 1);
    }

    printf("--------------- Testing hashFunction1 --------------- \n");

    assertTrue((hashFunction1("abc") == 294), "Hash 'abc' == 294");

    printf("--------------- Testing contains --------------- \n");

    assertTrue(containsKey(hashTable, "it") == 1, "Search for 'it'");
    assertTrue(containsKey(hashTable, "comparison") == 1,
               "Search for 'comparison'");
    assertTrue(containsKey(hashTable, "period") == 1, "Search for 'period'");
    assertTrue(containsKey(hashTable, "despair") == 1, "Search for 'despair'");
    assertTrue(containsKey(hashTable, "deriop") == 0, "Search for 'deriop'");
    assertTrue(containsKey(hashTable, "yuck") == 0, "Search for 'yuck'");

    printf("\n--------------- Testing table stats --------------- \n");

    assertTrue(hashTable->tableSize == 40, "Test table size (40)");
    assertTrue(fullBuckets(hashTable) == 30, "Test full buckets (30)");
    assertTrue(emptyBuckets(hashTable) == 10, "Test empty buckets (10)");
    assertTrue(linkCount(hashTable) == 59, "Test link count (59)");

    printf("--------------- Testing remove --------------- \n");

    assertTrue(containsKey(hashTable, "yuck") == 0, "Search for 'yuck'");
    removeKey(hashTable,
              "yuck"); /* Should print some type of 'not found' message */
    assertTrue(containsKey(hashTable, "despair") == 1, "Search for 'despair'");
    removeKey(hashTable, "despair");
    assertTrue(containsKey(hashTable, "despair") == 0,
               "Search for 'despair' after remove");

    printf("--------------- Printing hash table --------------- \n");
    printMap(hashTable);

    deleteMap(hashTable);

    printf("--------------- Testing Round 2 - Same text file - new hash "
           "--------------- \n");

    fn = "text1.txt"; /* the file name and path */
    printf("Opening file: %s \n", fn);
    filePtr = fopen(fn, "r");
    hashTable2 = createMap(40, 2);

    while ((word = getWord(filePtr)) != '\0') {
        insertMap(hashTable2, word, 1);
    }

    printf("--------------- Testing table stats 2 --------------- \n");

    assertTrue(hashTable2->tableSize == 80, "Test table size (80)");
    assertTrue(fullBuckets(hashTable2) == 38, "Test full buckets (38)");
    assertTrue(emptyBuckets(hashTable2) == 42, "Test empty buckets (42)");
    assertTrue(linkCount(hashTable2) == 59, "Test link count (59)");

    printf("--------------- Testing remove --------------- \n");


    assertTrue(containsKey(hashTable2, "yuck") == 0,
        "Search for 'yuck'");
    /* Should print some type of 'not found' message */
    removeKey(hashTable2, "yuck");
    assertTrue(containsKey(hashTable2, "despair") == 1,
        "Search for 'despair'");
    removeKey(hashTable2, "despair");
    assertTrue(containsKey(hashTable2, "despair") == 0,
        "Search for 'despair' after remove");
    assertTrue(containsKey(hashTable2, "belief") == 1,
        "Search for 'belief'");
    removeKey(hashTable2, "belief");
    assertTrue(containsKey(hashTable2, "belief") == 0,
        "Search for 'belief' after remove");
    assertTrue(containsKey(hashTable2, "degree") == 1,
        "Search for 'degree'");
    removeKey(hashTable2, "degree");
    assertTrue(containsKey(hashTable2, "degree") == 0,
        "Search for 'degree' after remove");

    printf("Closing file: %s \n", fn);
    fclose(filePtr);

    printf("--------------- Testing table stats 2 --------------- \n");

    struct hashMap *concord;

    fn = "text2.txt";
    printf("Opening file: %s \n", fn);
    filePtr = fopen(fn, "r");
    concord = createMap(10, 2);


    /* instead of calling insert, we call concordance */
    while((word = getWord(filePtr)) != '\0') {
        concordance(concord, word);
    }

    printf("--------------- Concordance table stats --------------- \n");

    printf("table size: %d \n", concord->tableSize);
    printf("full buckets: %d \n", fullBuckets(concord));
    printf("empty buckets: %d \n", emptyBuckets(concord));
    printf("link count: %d \n", linkCount(concord));

    /* Test further on your own */

    printMap(concord);

    assertTrue(
        hashFunction1("eleven plus two") ==
        hashFunction1("twelve plus one"),
        "hashFunction1 hashes anagrams the same"
    );

    return 0;
}
