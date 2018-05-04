#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rbt.h"
#include "mylib.h"

/**
 * Red black tree struct.
 * Stores strings in a self balancing BST e.g. a red black tree.
 * COSC242 Group Assignment, September 2017.
 * @author Daniela Lemow, Megan Seto and Nikolah Pearce.
 */

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

typedef enum {
    RED,
    BLACK
} rbt_colour;

struct rbtnode {
    char *key;
    rbt_colour colour;
    rbt left;
    rbt right;
};

/**
 * Right rotate the subtrees and root of the Red-Black tree.
 * @param r the Red-Black tree to rotate at the root.
 * @return the rotated Red-Black tree.
 */
static rbt right_rotate(rbt r) {
    rbt temp = r;
    r = r->left;
    temp->left = r->right;
    r->right = temp;
    return r;
}

/**
 * Left rotate the subtrees and root of the Red-Black tree.
 * @param r the Red-Black tree to rotate at the root.
 * @return the rotated Red-Black tree.
 */
static rbt left_rotate(rbt r) {
    rbt temp = r;
    r = r->right;
    temp->right = r->left;
    r->left = temp;
    return r;
}

/**
 * Recolour the root of the Red-Black tree, and the roots of its subtrees.
 * @param r the Red-Black tree to colour correct.
 * @return the Red-Black tree with its colours corrected.
 */
static rbt make_root_red(rbt r) {
    r->colour = RED;
    r->left->colour = BLACK;
    r->right->colour = BLACK;
    return r;
}

/**
 * Perform a right rotate on the Red-Black tree.
 * Then recolour the root and the root of its right subtree.
 * @param r the Red-Black tree to cortect.
 * @return the rotated Red-Black tree with its colours corrected.
 */
static rbt handle_right(rbt r) {
    r = right_rotate(r);
    r->colour = BLACK;
    r->right->colour = RED;
    return r;
}

/**
 * Perform a left rotate on the Red-Black tree.
 * Then recolour the root and the root of its left subtree.
 * @param r the Red-Black tree to correct.
 * @return the rotated Red-Black tree with its colours corrected.
 */
static rbt handle_left(rbt r) {
    r = left_rotate(r);
    r->colour = BLACK;
    r->left->colour = RED;
    return r;
}

/**
 * Fix the Red-Black tree by maintaining its Red-Blackness.
 * Rotate and recolour where conditions are violated.
 * @param r the Red-Black tree to fix and recolour.
 * @return the corrected Red-Black tree.
 */
static rbt rbt_fix(rbt r) {
    if (IS_RED(r->left) && IS_RED(r->left->left)) {
        if (IS_RED(r->right)) {
            r = make_root_red(r);
        } else {
            r = handle_right(r);
        }
    } else if (IS_RED(r->left) && IS_RED(r->left->right)) {
        if (IS_RED(r->right)) {
            r = make_root_red(r);
        } else {
            r->left = left_rotate(r->left);
            r = handle_right(r);
        }
    } else if (IS_RED(r->right) && IS_RED(r->right->left)) {
        if (IS_RED(r->left)) {
            r = make_root_red(r);
        } else {
            r->right = right_rotate(r->right);
            r = handle_left(r);
        }
    } else if (IS_RED(r->right) && IS_RED(r->right->right)) {
        if (IS_RED(r->left)) {
            r = make_root_red(r);
        } else {
            r = handle_left(r);
        }
    }    
    return r;
}

/**
 * Free all memory allocated in the Red-Black tree.
 * @param r the Red-Black tree to free.
 * @return the freed Red-Black tree.
 */
rbt rbt_free(rbt r) {
    if (r == NULL) {
        return r;
    }
    r->right = rbt_free(r->right);
    r->left = rbt_free(r->left);
    free(r->key);
    free(r);
    return r;
}

/**
 * Inserts a string into the Red-Black tree.
 * Recursively call rbt_fix after each insert.
 * @param r the Red-Black tree to insert into.
 * @param *str the string to insert.
 * @return the updated Red-Black tree.
 */
static rbt rbt_insert_recursive(rbt r, char *str) {
    if (r == NULL) {
        r = emalloc(sizeof *r);
        r->key = emalloc((strlen(str)+1) * sizeof (char));
        strcpy(r->key, str);
        r->colour = RED;
    } else if (strcmp(str, r->key) < 0 || strcmp(str, r->key) == 0) {
        r->left = rbt_insert_recursive(r->left, str);
    } else if (strcmp(str, r->key) > 0) {
        r->right = rbt_insert_recursive(r->right, str);
    }
    r = rbt_fix(r);
    return r;
}

/**
 * Inserts a string into the rbt by calling rbt_insert_recursive.
 * After the fixing, it ensure the root is black by colouring it black.
 * @param r the Red-Black tree to insert into.
 * @param *str the string to insert.
 * @return the updated Red-Black tree.
 */
rbt rbt_insert(rbt r, char *str) {
    r = rbt_insert_recursive(r, str);
    if (IS_RED(r)) {
        r->colour = BLACK;
    }
    return r;
}

/**
 * Create a new NULL Red-Black tree.
 * @return the new Red-Black tree.
 */
rbt rbt_new() {
    return NULL;
}

/**
 * Traverse the Red-Black tree  via "pre-order" and print out each key.
 * @param r the Red-Black tree to print out.
 * @param func(char *str) the print function to perform on each key.
 */
void rbt_preorder(rbt r, void f(char *str)) {
    if (r == NULL) {
        return;
    }
    f(r->key);
    rbt_preorder(r->left, f);
    rbt_preorder(r->right, f);
}

/**
 * Search the Red-Black tree for a string.
 * @param r the Red-Black tree to search.
 * @param *str the string to search for.
 * @return 1 if found succesfully, else 0.
 */
int rbt_search(rbt r, char *str) {
    if (r == NULL){
        return 0;
    } else {
        if (strcmp(str, r->key) == 0) {
            return 1;
        } else if ((r->left != NULL) && (strcmp(str, r->key) < 0)) {
            return rbt_search(r->left, str);
            
        } else if ((r->right != NULL) && (strcmp(str, r->key) > 0)){
            return rbt_search(r->right, str);
        }
        return 0;
    }
}
