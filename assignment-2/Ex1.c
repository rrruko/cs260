/* CS260 - Assignment 2 - EX 1*/
/* Name: Ethan Jones
 * Date: 20-1-2018
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>

#define bool char

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

// Close enough
bool isSpace(char ch) {
    return ch == ' '
        || ch == '\t'
        || ch == '\n';
}

/*
    Desc: Stick all the words in a string together and put a new \0 at
        the end.
    Pre: A null byte-terminated mutable string.
    Post: All the spaces are gone (only handles 0x20 SPACE, not e.g. tabs)
*/
void removeSpaces(char* word) {
    int i;
    int j = 0;
    for (i = 0; word[j] != '\0'; i++, j++) {
        while (isSpace(word[j])) {
            j++;
        }
        word[i] = word[j];
    }
    word[i] = '\0';
}

/*
    Desc: Convert a string to pascal case.
    Pre: A null byte-terminated mutable string.
    Post: The first letter of each word is capitalized, all other letters are
        made lowercase, and all the spaces are removed.
*/
void PascalCase(char* word) {
    if (isLower(word[0])) {
        word[0] = toUpperCase(word[0]);
    }

    int i;
    for (i = 1; word[i] != '\0'; i++) {
        if (isSpace(word[i - 1]) && isLower(word[i])) {
            word[i] = toUpperCase(word[i]);
        } else if (!isSpace(word[i - 1]) && isUpper(word[i])) {
            word[i] = toLowerCase(word[i]);
        }
    }

    removeSpaces(word);
}

int main() {

    /* Read word from the keyboard using scanf
	Max length 100 characters including string terminator */
    char buffer[100];
    scanf("%[^\n]", buffer);

    /* Call PascalCase */
    PascalCase(buffer);

    /* Print the new word */
    printf("%s\n", buffer);

    return 0;
}
