#include "bst.h"

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

/*
    printTestResult: function to print the result of a test function
    param1: predicate - the result of the test
    param2: nameTestFunction - name of the function being tested
    param3: message - message passed to the test function
    post: result is printed to standard output
*/
void printTestResult(int predicate, char *nameTestFunction, char *message) {
    if (predicate) {
       printf("%s() - %s: PASS\n",nameTestFunction, message);
    } else {
       printf("%s() - %s: FAIL\n",nameTestFunction, message);
    }
}


/*
    testAddNode: function to test each node of the BST and children
    pre: tree is not null
    param: tree - the tree we are testing
    post: none
*/
void testAddNode(struct BSTree *tree) {
    assert(tree != NULL);
    printf("------------------testing add node-------------------\n");

    addBSTree(tree, 55);
    printTestResult((tree->root->val == 55) && (tree->cnt == 1), "addNode", "test add 55");

    addBSTree(tree, 36);
    printTestResult((tree->root->left->val == 36) && (tree->cnt == 2), "addNode", "test add 36");

    addBSTree(tree, 78);
    printTestResult((tree->root->right->val == 78) && (tree->cnt == 3), "addNode", "test add 78");

    addBSTree(tree, 20);
    printTestResult((tree->root->left->left->val == 20) && (tree->cnt == 4), "addNode", "test add 20");

    addBSTree(tree, 85);
    printTestResult((tree->root->right->right->val == 85) && (tree->cnt == 5), "addNode", "test add 85");

    addBSTree(tree, 67);
    printTestResult((tree->root->right->left->val == 67) && (tree->cnt == 6), "addNode", "test add 67");

    printf("--------------finished testing addNode-------------\n");
}

/*
    testContainsBSTree: function to test that the BST contains the elements that we added to it
    pre: tree is not null
    param: tree - the tree we are testing
    post: none
*/
void testContainsBSTree(struct BSTree *tree) {
    assert(tree != NULL);
    printf("------------------testing containsBST-------------------\n");

    printTestResult(containsBSTree(tree, 55), "containsBSTree", "test contains 55");
    printTestResult(containsBSTree(tree, 36), "containsBSTree", "test contains 36");
    printTestResult(containsBSTree(tree, 20), "containsBSTree", "test contains 20");
    printTestResult(containsBSTree(tree, 85), "containsBSTree", "test contains 85");
    printTestResult(!containsBSTree(tree, 88), "containsBSTree", "when test containing 88, which is not in the tree");

    printf("------------------finished testing containsBST-------------------\n");
}

/*
    testLeftMost: function to test the left most element
    param: tree - the tree we are testing
    pre: tree is not null
    post: none
*/
void testLeftMost(struct BSTree *tree) {
    assert(tree != NULL);
    printf("------------------testing testLeftMostValue-------------------\n");

    printTestResult(_leftMostValue(tree->root) == 20, "_leftMostValue", "leftmost of root");
    printTestResult(_leftMostValue(tree->root->left) == 20, "_leftMostValue", "leftmost of left subtree");
    printTestResult(_leftMostValue(tree->root->right) == 67, "_leftMostValue", "leftmost of right subtree");

    printf("------------------finished testing testLeftMostValue-------------------\n");
}

/*
    testRemoveNode: function to test the left most element
    param: tree - the tree we are testing
    pre: tree is not null
    post: 3 nodes have been removed from the tree
*/
void testRemoveNode(struct BSTree *tree) {
    assert(tree != NULL);
    printf("------------------testing removeNode-------------------\n");

    removeNodeFromTree(tree, 13);
    /* Should output: node is not contained in the tree */

    removeNodeFromTree(tree, 20);
    printTestResult((tree->root->val == 55) && (!containsBSTree(tree, 20)), "removeNodeFromTree", "remove 20");

    removeNodeFromTree(tree, 67);
    printTestResult((tree->root->val == 55)  && (!containsBSTree(tree, 67)), "removeNodeFromTree", "remove 67");

    removeNodeFromTree(tree, 55);
    printTestResult((tree->root->val == 78) && (tree->root->left->val == 36) & (tree->root->right->val == 85) && (!containsBSTree(tree, 55)), "removeNodeFromTree", "remove 55(root)");

    removeNodeFromTree(tree, 78);
    printTestResult((tree->root->val == 85) && (tree->root->left->val == 36) && (tree->root->right == NULL),
        "removeNodeFromTree", "remove 78");

    removeNodeFromTree(tree, 85);
    printTestResult((tree->root->val == 36) && (tree->root->left == NULL) && (tree->root->right == NULL),
        "removeNodeFromTree", "remove 85");

    removeNodeFromTree(tree, 36);
    printTestResult((tree->root == NULL), "removeNodeFromTree", "remove 36");

    printf("------------------finished testing removeNode-------------------\n");
}

/*
    testLogNSearch: search a large binary tree to demonstrate that it's fast
*/
void testLogNSearch() {
    struct BSTree* tree = newBSTree();
    int n = 10000000;
    printf("Building a tree with %d random elements\n", n);
    int i;
    for (i = 0; i < n; i++) {
        float r = (float)(rand() % n) / (float)n;
        addBSTree(tree, r);
    }
    printf("Searching the tree\n");
    for (i = 0; i < 10; i++) {
        float r = (float)(rand() % n) / (float)n;
        printf("Tree contains %f: %d\n", r, containsBSTree(tree, r));
    }
    free(tree);
}

/*  Main function for testing different functions of the assignment
    Calls several specific testing routines (insert, delete, display, etc)
*/
int main() {
    struct BSTree *tree    = newBSTree();

    testAddNode(tree);
    testContainsBSTree(tree);
    testLeftMost(tree);
    testRemoveNode(tree);
    printTestResult(isEmptyBSTree(tree), "isEmptyBSTree", "tree is empty");
    addBSTree(tree, 15);
    addBSTree(tree, 4);
    addBSTree(tree, 8);
    addBSTree(tree, 23);
    addBSTree(tree, 16);
    addBSTree(tree, 42);

    printf("------------printing in-order traversal------------ \n");
    inorderTraversal(tree->root);

    printf("\n------------printing pre-order traversal------------ \n");
    preorderTraversal(tree->root);

    printf("\n------------printing post-order traversal------------ \n");
    postorderTraversal(tree->root);
    printf("\n");


    freeBSTree(tree);

    testLogNSearch(tree);
    return 0;
}

