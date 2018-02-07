#include "skipList.h"
#include <malloc.h>

int main() {
    /* initialize list one - max depth 4 */
    int cap = 4;
    struct skipList *list;
    list = malloc(sizeof(struct skipList) + sizeof(struct sLink)*cap);
    initSkipList(list, cap);

    printf("\n-------*****------- Static Test -------*****-------\n");
    staticTest(list);

    /* initialize list two - max depth 8  - comment & un-comment the test function accordingly*/
    cap = 8;
    struct skipList *list2;
    list2 = malloc(sizeof(struct skipList) + sizeof(struct sLink)*cap+1);
    initSkipList(list2, cap);

    printf("\n-------*****------- Dynamic Test -------*****-------\n");
    test(list2);

    return 0;
}

/*
    staticTest: Function tests the addValTest, printLv and removeLink functions
    pre: list is not null
    param1: list - the list
    post: links are added to the list at varying levels
    post: results are displayed via standard output
*/
void staticTest(struct skipList *list) {
    printf("\n-------------- Testing addValTest --------------\n");
    addValTest(list, 2, 1);
    addValTest(list, 6, 1);
    addValTest(list, 4, 1);
    addValTest(list, 5, 2);
    addValTest(list, 10, 2);
    addValTest(list, 3, 2);
    addValTest(list, 7, 1);
    addValTest(list, 9, 4);
    addValTest(list, 8, 3);
    addValTest(list, 15, 3);
    addValTest(list, 13, 1);

    printf("\n-------------- Testing printLv --------------\n");
    printLv(list, 1);
    /* should display: 2, 3, 4, 5, 6, 7, 8, 9, 10, 13, 15 */
    printLv(list, 2);
    /* should display: 3, 5, 8, 9, 10, 15 */
    printLv(list, 3);
    /* should display: 8, 9, 15 */
    printLv(list, 4);
    /* should display: 9 */

    printf("\n-------------- Testing searchVal --------------\n");
    printf("Search for 4: returned: %d \n", searchVal(list,4));
    printf("Search for 1: returned: %d \n", searchVal(list,1));
    printf("Search for 15: returned: %d \n", searchVal(list,15));

    printf("\n-------------- Testing removeLink --------------\n");
    printf("Removing 2 from list \n");
    removeLink(list, 2);
    printf("Removing 5 from list \n");
    removeLink(list, 5);
    printf("Removing 5 from list \n");
    removeLink(list, 5);

    printf("\n-------------- Testing printLv --------------\n");
    printLv(list, 1);
    /* should display: 3, 4, 6, 7, 8, 9, 10, 13, 15 */
    printLv(list, 2);
    /* should display: 3, 8, 9, 10, 15 */
    printf("\n-------*****------- Testing Complete -------*****-------\n");

}

/*
    test: Function tests the addVal, printLv and removeLink functions with a random, large set
    pre: list is not null
    param1: list - the list
    post: links are added to the list at varying levels
    post: results are displayed via standard output
*/
void test(struct skipList *list) {
    int i = 0;

    while(i < 25) {
        addVal(list, rand()%1000);
        i++;
    }

    printLv(list, 1);
    printLv(list, 2);
    printLv(list, 3);
    printLv(list, 4);
    printLv(list, 5);
    printLv(list, 6);
    printLv(list, 7);
    printLv(list, 8);

    printf("currMax: %d\n", list->currMax);

    printf("Search for 50: returned: %d \n", searchVal(list, 50));
    printf("Search for 0: returned: %d \n", searchVal(list, 0));
    printf("Search for 195: returned: %d \n", searchVal(list, 195));
    printf("Search for 862: returned: %d \n", searchVal(list, 862));
    printf("Search for 929: returned: %d \n", searchVal(list, 929));
    /* Verify your own results */
}
