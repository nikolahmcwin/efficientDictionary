#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "container.h"
#include "flexarray.h"
#include "rbt.h"

/**
 * Container struct.
 * Defines the type of container to be used.
 * Calls the necessary methods depending on the type.
 * COSC242 Group Assignment, September 2017.
 * @author Daniela Lemow, Megan Seto and Nikolah Pearce.
 */

struct containerrec {
    container_t type;
    void *contents;
};

/**
* Insert a new key into the hashtable container.
* Checks the type and calls the appropriate method for the container.
* @param c the container to insert into.
* @param *word the key to insert.
*/
void container_add(container c, char *word) {
    if (c->type == RED_BLACK_TREE) {
        c->contents = rbt_insert(c->contents, word);
    } else {
        flexarray_append(c->contents, word);
    }
}

/**
 * Frees the allocated memory for the container.
 * Checks the type and calls the appropriate method for the container.
 * @param c the container to free.
 */
void container_free(container c) {
    if (c->type == RED_BLACK_TREE) {
        rbt_free(c->contents);
    } else {
        flexarray_free(c->contents);
    }
    free(c);
}

/**
 * Creates and initialises a new container.
 * Checks the type and calls the appropriate method for the container.
 * @param t the enum type of container_t.
 * @return the new container.
 */
container container_new(container_t t) {
  container result = emalloc (sizeof *result);
  result->type = t;
  if (result->type == RED_BLACK_TREE) {
      result->contents = rbt_new();
  } else {
      result->contents = flexarray_new();
  }
  return result;
} 

/**
 * Print out each key in the container.
 * Checks the type and calls the appropriate method for the container.
 * @param c the container to print.
 * @param func(char *str) the print function to perform on each key.
 */
void container_print(container c, void func(char *str)) {
    if (c->type == RED_BLACK_TREE) {
        rbt_preorder(c->contents, func);
    } else {
        flexarray_visit(c->contents, func);
    }
}

/**
 * Search the container for a string.
 * Checks the type and calls the appropriate method for the container.
 * @param c the container to search.
 * @param *word the string to search for.
 * @return 1 if found successfully, else 0.
 */
int container_search(container c, char *word) {
    if (c->type == RED_BLACK_TREE) {
        return rbt_search(c->contents, word);
    } else {
        return flexarray_is_present(c->contents, word);
    }
}

