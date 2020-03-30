// Implementation of the BST ADT using an AVL tree

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Time.h"
#include "Tree.h"

typedef struct node *Node;
struct node {
    Time time;
    int  height;
    Node left;
    Node right;
};

struct tree {
    Node root;
};

////////////////////////////////////////////////////////////////////////
// Function Prototypes

static void doFree(Node n);
static Node doInsert(Node n, Time time);
static Node rotateLeft(Node n);
static Node rotateRight(Node n);
static int  height(Node n);
static int  max(int a, int b);
static Node newNode(Time time);

////////////////////////////////////////////////////////////////////////
// Constructor and Destructor

// Creates a new empty tree
Tree TreeNew(void) {
    Tree t = malloc(sizeof(*t));
    if (t == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    t->root = NULL;
    return t;
}

// Frees all memory associated with the given tree
void TreeFree(Tree t) {
    doFree(t->root);
    free(t);
}

static void doFree(Node n) {
    if (n != NULL) {
        doFree(n->left);
        doFree(n->right);
        TimeFree(n->time);
        free(n);
    }
}

////////////////////////////////////////////////////////////////////////
// Insertion

// Inserts  a  copy of the given time into the tree if it is not already
// in the tree
void TreeInsert(Tree t, Time time) {
    t->root = doInsert(t->root, time);
}

static Node doInsert(Node n, Time time) {
    if (n == NULL) {
        return newNode(time);
    }
    // insert recursively
    int cmp = TimeCmp(time, n->time);
    if (cmp < 0) {
        n->left = doInsert(n->left, time);
    } else if (cmp > 0) {
        n->right = doInsert(n->right, time);
    } else { // (cmp == 0)
        // if time is already in the tree,
        // we can return straight away
        return n;
    }

    // insertion done
    // correct the height of the current subtree
    n->height = 1 + max(height(n->left), height(n->right));

    
    // rebalance the tree
    // TODO: Add your code here and change
    //       the return statement if needed
    if (height(n->left) - height(n->right) > 1) {
        int cmp = TimeCmp(time, n->left->time);
        if (cmp > 0) {
            n->left = rotateLeft(n->left);
            n = rotateRight(n);
        } else {
            n = rotateRight(n);
        }
    } else if (height(n->right) - height(n->left) > 1) {
        int cmp = TimeCmp(time, n->right->time);
        if (cmp < 0) {
            n->right = rotateRight(n->right);
            n = rotateLeft(n);
        } else {
            n = rotateLeft(n);
        }
    }
    return n;
}

static Node newNode(Time time) {
    Node n = malloc(sizeof(*n));
    if (n == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }

    n->time = TimeCopy(time);
    n->height = 0;
    n->left = NULL;
    n->right = NULL;
    return n;
}

// Rotates  the  given  subtree left and returns the root of the updated
// subtree.
static Node rotateLeft(Node n) {
    if (n == NULL || n->right == NULL) {
        return n;
    }
    Node n_right_side = n->right;

    n->right = n_right_side->left;
    n_right_side->left = n;
    
    if (n_right_side->right != NULL)
        n_right_side->right->height = 1 + max(height(n_right_side->right->left), height(n_right_side->right->right));
    if (n->left != NULL)
        n->left->height = 1 + max(height(n->left->left), height(n->left->right));
    n->height = 1 + max(height(n->left), height(n->right));
    n_right_side->height = 1 + max(height(n_right_side->left), height(n_right_side->right));
    return n_right_side;
}

// Rotates the given subtree right and returns the root of  the  updated
// subtree.
static Node rotateRight(Node n) {
    // There's nothing on the left so return n 
    // no rotation will be performed
    if (n == NULL || n->left == NULL) {
        return n;
    }
    Node n_left_side = n->left;
    // n->height--;
    // if (n->right != NULL)
    //     n->right->height--;
    // n_left_side->height++;
    // if (n_left_side->left != NULL)
    //     n_left_side->left->height++;
    n->left = n_left_side->right;
    n_left_side->right = n;

    if (n_left_side->right != NULL)
        n_left_side->right->height = 1 + max(height(n_left_side->right->left), height(n_left_side->right->right));
    if (n->right != NULL)
        n->right->height = 1 + max(height(n->right->left), height(n->right->right));
    n->height = 1 + max(height(n->left), height(n->right));
    n_left_side->height = 1 + max(height(n_left_side->left), height(n_left_side->right));

    return n_left_side;
}

// Returns  the height of a subtree while assuming that the height field
// of the root node of the subtree is correct
static int height(Node n) {
    if (n == NULL) {
        return -1;
    } else {
        return n->height;
    }
}

static int max(int a, int b) {
    return a > b ? a : b;
}

////////////////////////////////////////////////////////////////////////
// Specialised Operations

Time TreeFloorFinding(Node t, Time time,  Time *closest_time) {
    if (t == NULL) {
        return t->time;
    }
    int cmp_after = TimeCmp(time, t->time);
    if (cmp == 0) {
        return t->time;
    } else if (cmp < 0) {
        if (t->left == NULL) {
            return t->time;
        }
        if (cmp_after > 0) {
            return t->time;
        }
        return TreeFloorFinding(t->left, time, closest_time);
    } else {
        if (t->right == NULL) {
            return t->time;
        }
        return TreeFloorFinding(t->right, time, closest_time);
    }
}

Time TreeCeilingFinding(Node t, Time time) {
    if (t == NULL) {
        return t->time;
    }
    int cmp = TimeCmp(time, t->time);
    if (cmp == 0) {
        return t->time;
    } else if (cmp < 0) {
        if (t->left == NULL) {
            return TreeCeilingFinding(t->right, time);
        }
        return TreeCeilingFinding(t->left, time);
    } else {
        if (t->right == NULL) {
            return t->time;
        }
        return TreeCeilingFinding(t->right, time);
    }
}
// Returns the latest time in the tree that is earlier than or equal  to
// the  given  time,  or  NULL if no such time exists. The returned time
// should not be modified or freed.
Time TreeFloor(Tree t, Time time) {
    // TODO: Add your code here and change
    //       the return statement if needed
    //       You can create helper functions
    //       if needed
    Time closest_time = NULL; 
    if (t == NULL) {
        return NULL;
    }
    int cmp = TimeCmp(time, t->root->time);
    if (cmp == 0) {
        return t->root->time;
    } else if (cmp < 0) {
        return TreeFloorFinding(t->root->left, time, &closest_time);
    } else {
        return TreeFloorFinding(t->root->right, time, &closest_time);
    }

    // return NULL;
}



// Returns the earliest time in the tree that is later than or equal  to
// the  given  time,  or  NULL if no such time exists. The returned time
// should not be modified or freed.
Time TreeCeiling(Tree t, Time time) {
    // TODO: Add your code here and change
    //       the return statement if needed
    //       You can create helper functions
    //       if needed
    // if (t == NULL) {
    //     return NULL;
    // }
    // int cmp = TimeCmp(time, t->root->time);
    // if (cmp == 0) {
    //     return t->time;
    // } else if (cmp > 0) {
    //     return TreeFloor(t->root->left, time);
    // } else {
    //     return TreeFloor(t->root->right, time);
    // }

    return NULL;
}

////////////////////////////////////////////////////////////////////////
// Printing

//////////////////
// List the items

static void doList(Node n);

void TreeList(Tree t) {
    doList(t->root);
}

static void doList(Node n) {
    if (n != NULL) {
        doList(n->left);
        TimeShow(n->time);
        printf("\n");
        doList(n->right);
    }
}

///////////////////////////
// Show the tree structure

typedef unsigned long long uint64;
static void doShow(Node n, int level, uint64 arms);

void TreeShow(Tree t) {
    if (t->root != NULL && t->root->height >= 64) {
        printf("Tree is too tall!\n");
    } else {
        doShow(t->root, 0, 0);
    }
}

// This  function  uses a hack to determine when to draw the arms of the
// tree and relies on the tree being reasonably balanced. Don't  try  to
// use this function if the tree is not an AVL tree!
static void doShow(Node n, int level, uint64 arms) {
    if (n == NULL) return;

    TimeShow(n->time);
    printf(" (height: %d)\n", n->height);

    if (n->left != NULL) {
        for (int i = 0; i < level; i++) {
            if ((1LLU << i) & arms) {
                printf("│     ");
            } else {
                printf("      ");
            }
        }
        printf("%s", n->right != NULL ? "┝━╸L: " : "┕━╸L: ");
        if (n->right != NULL) {
            arms |= (1LLU << level);
        } else {
            arms &= ~(1LLU << level);
        }
        doShow(n->left, level + 1, arms);
    }

    if (n->right != NULL) {
        // if (n->left != NULL) {
        //     for (int i = 0; i <= level; i++) {
        //         if ((1LLU << i) & arms) {
        //             printf("│     ");
        //         } else {
        //             printf("      ");
        //         }
        //     }
        //     printf("\n");
        // }
        for (int i = 0; i < level; i++) {
            if ((1LLU << i) & arms) {
                printf("│     ");
            } else {
                printf("      ");
            }
        }
        printf("┕━╸R: ");
        arms &= ~(1LLU << level);
        doShow(n->right, level + 1, arms);
    }
}

////////////////////////////////////////////////////////////////////////
// Testing
// All  functions below exist for testing purposes ONLY. Do NOT use them
// in your code.

static Node doInsertLeaf(Node n, Time time);

void TreeRotateLeftAtRoot(Tree t) {
    t->root = rotateLeft(t->root);
}

void TreeRotateRightAtRoot(Tree t) {
    t->root = rotateRight(t->root);
}

void TreeInsertLeaf(Tree t, Time time) {
    t->root = doInsertLeaf(t->root, time);
}

static Node doInsertLeaf(Node n, Time time) {
    if (n == NULL) {
        return newNode(time);
    }

    int cmp = TimeCmp(time, n->time);
    if (cmp < 0) {
        n->left = doInsertLeaf(n->left, time);
    } else if (cmp > 0) {
        n->right = doInsertLeaf(n->right, time);
    }

    n->height = 1 + max(height(n->left), height(n->right));
    return n;
}
