#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "flexarray.h"

/**
 * Flexarray struct.
 * Acts as a flexible array that can expand as needed.
 * COSC242 Group Assignment, September 2017.
 * @author Daniela Lemow, Megan Seto and Nikolah Pearce.
 */
 
struct flexarrayrec {
    int capacity;
    int itemcount;
    char **items;
};

/**
 * Adds a new string to the flexarray.
 * Checks the capacity and expands and reallocates memory as required.
 * @param f the flexarray to append to.
 * @param *str the string to append.
 */
void flexarray_append(flexarray f, char *str) {
    if (f->itemcount == f->capacity) {
        f->capacity += f->capacity;
        f->items = erealloc(f->items, f->capacity * sizeof f->items[0]);
    }
    f->items[f->itemcount] = emalloc((strlen(str)+1) * sizeof (char));
    strcpy(f->items[f->itemcount], str);
    f->itemcount++;
}

/**
 * Free the memory allocated in the flexarray.
 * @param f the flexarray to free.
 */
void flexarray_free(flexarray f) {
    int i;
    for (i = 0; i < f->itemcount; i++) {
        free(f->items[i]);
    }
    free(f->items);
    free(f);
}

/**
 * Search the flexarray for a string.
 * @param f the flexarray to search.
 * @param *str the string to seach for.
 * @return 1 if found successfully, else 0.
 */
int flexarray_is_present(flexarray f, char *str) {
    int i;
    for (i = 0; i < f->itemcount; i++) {
        if (strcmp(f->items[i], str) == 0) {
            return 1;
        }
    }   
    return 0;
}

/**
 * Create and initialise a new flexarray.
 * @return the new flexarray.
 */
flexarray flexarray_new() {
    flexarray result = emalloc(sizeof *result);
    result->capacity = 2;
    result->itemcount = 0;
    result->items = emalloc(result->capacity * sizeof result->items[0]);
    return result;
}

/**
 * Print out the flexarray contents in a "pre-order" type traversal.
 * @param f the flexarray to print.
 * @param func(char *str) the print function to perform on each key.
 */
void flexarray_visit(flexarray f, void func(char *s)) {
    int i;
    for (i = 0; i < f->itemcount; i++) {
        func(f->items[i]);   
    }
    return;
}

