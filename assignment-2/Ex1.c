/* CS260 - Assignment 2 - EX 1*/
/* Name: Ethan Jones
 * Date: 20-1-2018
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>

#define bool int

/*
    Desc: converts ch to upper case
    Precondition: ch is a lower case char (a-z).
    Postcondition: ch is return as upper case.
*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*
    Desc: converts ch to lower case
    Precondition: ch is a upper case char (a-z).
    Postcondition: ch is return as lower case.
*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

bool isUpper(char ch) {
    return ch >= 'A' && ch <= 'Z';
}

bool isLower(char ch) {
    return ch >= 'a' && ch <= 'z';
}

/*
    Desc: O(n). Stick all the words in a string together and put a new \0 at
        the end.
    Pre: A null byte-terminated mutable string.
    Post: All the spaces are gone (only handles 0x20 SPACE, not e.g. tabs)
*/
void removeSpaces(char* word) {
    int i;
    int j = 0;
    for (i = 0; word[j] != '\0'; i++, j++) {
        while (word[j] == ' ') {
            j++;
        }
        word[i] = word[j];
    }
    word[i] = '\0';
}

void PascalCase(char* word) {
    /* Convert to Pascal case
        It is safe to assume that he string is terminated by '\0' */
    word[0] = toUpperCase(word[0]);

    int i;
    for (i = 1; word[i] != '\0'; i++) {
        if (word[i - 1] == ' ' && isLower(word[i])) {
            word[i] = toUpperCase(word[i]);
        } else if (word[i - 1] != ' ' && isUpper(word[i])) {
            word[i] = toLowerCase(word[i]);
        }
    }

    removeSpaces(word);
}

void testPascalCase() {
    char s[] = "tHe bEsT Of tImEs";
    PascalCase(s);
    printf("%s\n", s);
}

int main() {
    testPascalCase();

    /* Read word from the keyboard using scanf
	Max length 100 characters including string terminator */

    /* Call PascalCase */
    
    /* Print the new word */
    
    return 0;
}
