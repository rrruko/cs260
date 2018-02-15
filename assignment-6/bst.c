/*
    Name: Ethan Jones
    Date: 2018-02-14
    Desc: Binary search tree functions
*/

#include "bst.h"

/*
    compareValues: function returns an integer to tell you if the left value is
    greater then, less then, or equal to the right value.
    used to compare node values
    pre: none
    post: none
    return: integer value is returned according to rules below:
    if left < right return -1
    if left > right return 1
    if left = right return 0
 */
int compareValues(TYPE left, TYPE right) {
    if (left < right) {
        return -1;
    } else if (left > right ){
        return 1;
    } else {
        return 0;
    }
}

/*
    initBSTree: function to initialize the binary search tree.
    param1: tree
    pre: tree is not null
    post: tree size is 0
    post: root is null
 */
void initBSTree(struct BSTree *tree) {
    assert(tree != NULL);
    tree->cnt  = 0;
    tree->root = NULL;
}

/*
    newBSTree: function to create a binary search tree.
    param: none
    pre: none
    return: returns an empty tree
    function calls initBSTree
 */
struct BSTree* newBSTree() {
    struct BSTree *tree = (struct BSTree *)malloc(sizeof(struct BSTree));
    assert(tree != NULL);

    initBSTree(tree);
    return tree;
}

/*
    freeBSTree: function to clear the nodes of a binary search tree
    param: tree a binary search tree
    pre: tree not null
    post: the nodes of the tree are deallocated, as well as the tree itself
    tree->root = 0;
    tree->cnt = 0
    nodes are removed by _freeNodes
 */
void freeBSTree(struct BSTree *tree) {
    assert(tree != NULL);
    _freeNodes(tree->root);
    tree->root = NULL;
    tree->cnt  = 0;
    free(tree);
    printf("tree freed \n");
}

/*
    _freeNodes: function to free the nodes of a binary search tree
    param: node - the root node of the tree to be freed
    pre: node is not null
    post: node and all descendants are deallocated
*/
void _freeNodes(struct Node *node) {
    if (node != NULL) {
        _freeNodes(node->left);
        _freeNodes(node->right);
        free(node);
    }
}

/*
    isEmptyBSTree: function to determine if  a binary search tree is empty.
    param: tree the binary search tree
    pre:  tree is not null
    return: return 1 if the tree is empty, otherwise return 0
 */
int isEmptyBSTree(struct BSTree *tree) {
    return tree->root == NULL;
}

int sizeSubtree(struct Node* node) {
    if (node == NULL) {
        return 0;
    } else {
        return 1 + sizeSubtree(node->left) + sizeSubtree(node->right);
    }
}

/*
    sizeBSTree: function to determine the size of a binary search tree
    param: tree - the BST
    pre: tree is not null
    return: return the size of the tree
*/
int sizeBSTree(struct BSTree *tree) {
    assert(tree != NULL);
    return sizeSubtree(tree->root);
}

/*
    addBSTree: function to add a value to the binary search tree
    param1: tree - the binary search tree
    param2: val    - the value to be added to the tree
    pre: tree is not null
    post: cnt is incremented
    _addNode handles the actual add
 */
void addBSTree(struct BSTree *tree, TYPE val) {
    printf("Adding %.1f \n", val);
    if (tree->root == NULL) {
        struct Node* new = malloc(sizeof(struct Node));
        new->left = NULL;
        new->right = NULL;
        new->val = val;
        tree->root = new;
    } else {
        tree->root = _addNode(tree->root, val);
    }
    tree->cnt++;
}

/*
    _addNode: function to add a value to the binary search tree
    param1: curr - the current node
    param2: val    - the value to be added to the tree
    pre: curr is not null
    post: tree now contains val
 */
struct Node *_addNode(struct Node *curr, TYPE val) {
    if (val < curr->val) {
        if (curr->left == NULL) {
            struct Node* new = malloc(sizeof(struct Node));
            new->left = NULL;
            new->right = NULL;
            new->val = val;
            curr->left = new;
        } else {
            curr->left = _addNode(curr->left, val);
        }
    } else if (val > curr->val) {
        if (curr->right == NULL) {
            struct Node* new = malloc(sizeof(struct Node));
            new->left = NULL;
            new->right = NULL;
            new->val = val;
            curr->right = new;
        } else {
            curr->right = _addNode(curr->right, val);
        }
    }

    return curr;
}

/*
    containsBSTree: function to determine if the binary search tree contains an
    element - calls _containsNode
    param1: tree the binary search tree
    param2: val    - the value to search for in the tree
    pre: tree is not null
    post: return 1 if the tree contains the value, otherwise return 0
 */
int containsBSTree(struct BSTree *tree, TYPE val) {
    assert(tree != NULL);
    return _containsNode(tree->root, val);
}

/*
    _containsNode: function checks for for the value in a binary search tree
    param1: curr - the current node
    param2: val    - the value to be removed from the tree
    pre: curr is not null
    post: return 1 if found, otherwise return 0
*/
int _containsNode(struct Node *curr, TYPE val) {
    /* FIX ME */

    return 0;

}



/*
    removeNodeFromTree: function to remove a value from the binary search tree - calls _removeNode
    param1: tree - the binary search tree
    param2: val    - the value to be removed from the tree
    pre: tree is not null
    pre: val is in the tree
    post: tree size is reduced by 1
*/
void removeNodeFromTree(struct BSTree *tree, TYPE val) {
    if (containsBSTree(tree, val)) {
        tree->root = _removeNode(tree->root, val);
        tree->cnt--;
    } else {
        printf("node is not contained in the tree \n");
    }
}

/*
    _removeNode: remove a node from the tree - recursive implementation
    param1: curr - the current node
    param1: val - the value to be removed from the tree
    pre: val is in the tree
    pre: curr is not null
    post: descendant of curr containing val is removed from the tree
    HINT - There are 3 cases: the node is a leaf, the node has only one
    subtree, the node has two subtrees use leftmost to get the value (when
    needed) and removeLeftmost (when needed).
 */
struct Node *_removeNode(struct Node *curr, TYPE val) {
    /* FIX ME */

    return curr;

}

/*
    _leftMostValue: helper function to find the left most child of a node -
    iterative implementation
    param: curr the current node
    pre: curr is not null
    post: return the value of the left most child of curr
*/
TYPE _leftMostValue(struct Node *curr) {
    while(curr->left != NULL) {
            curr = curr->left;
    }
    return curr->val;
}


/*
    _removeLeftMost: helper function to remove the left most child of a node -
    iterative implementation
    param: curr - the current node
    post: the leftmost node of curr is not in the tree
 */
void _removeLeftMost(struct Node *curr) {
    if(curr->left == NULL) {
        printf("left subtree is empty \n");
        return;
    }
    struct Node *curr_parent = curr;
    while(curr->left != NULL) {
            curr_parent = curr;
            curr = curr->left;
    }
    curr_parent->left = NULL;
    free(curr);
    printf("leftmost node removed \n");
}

/*
    inorderTraversal: inorder traversal of tree left-node-right
    param: curr - the current node
    pre: curr is not null
    post: in-order traversal s printed
*/
void inorderTraversal(struct Node *curr) {
    /* FIX ME */

}

/*
    preorderTraversal: inorder traversal of tree node-left-right
    param: curr - the current node
    pre: curr is not null
    post: pre-order traversal s printed
*/
void preorderTraversal(struct Node *curr) {
    /* FIX ME */

}

/*
    postorderTraversal: post-order traversal of tree left-right-node
    param: curr - the current node
    pre: curr is not null
    post: post-order traversal s printed
*/
void postorderTraversal(struct Node *curr) {
    /* FIX ME */

}
