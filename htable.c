#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mylib.h"
#include "container.h"
#include "htable.h"

/**
 * Htable struct.
 * Creates hashkeys, maps strings and stores them within.
 * Uses a a container chaining method.
 * COSC242 Group Assignment, September 2017.
 * @author Daniela Lemow, Megan Seto and Nikolah Pearce.
 */
 
struct htablerec {
    int capacity;
    int count;
    container_t type;
    container *hashtable;
};

/**
 * Converts a string into an integer value via a hash function.
 * @param *word the key to convert.
 * @return the integer 'hashkey' value, unsigned.
 */
static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;
    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}

/**
 * Frees all memory allocated in the hashtable via "post-order".
 * @param h the hashtable to free.
 */
void htable_free(htable h) {
    int i;
    for (i = 0; i < h->capacity; i++) {
        if (h->hashtable[i] != NULL) {
            container_free(h->hashtable[i]);
        }
    }
    free(h->hashtable);
    free(h);
}

/**
 * Insert a new key into the hashtable.
 * @param h the hashtable to insert into.
 * @param *str the key to insert.
 * @return 1 if successfully inserted, else 0.
 */
int htable_insert(htable h, char *str) {
    unsigned int hashkey = htable_word_to_int(str);
    unsigned int position = (hashkey % (h->capacity));
    
    if (h->hashtable[position] == NULL) {
        container c = container_new(h->type);
        container_add(c, str);
        h->hashtable[position] = c;
        h->count++;
        return 1;
        
    } else if (h->hashtable[position] != NULL) {
        container_add(h->hashtable[position], str);
        h->count++;
        return 1;
        
    }
    return 0;
}

/**
 * Creates and initializes a new htable.
 * Sets hashtables entries to NULL.
 * @param capacity the maximum number of containers to use in the hashtable.
 * @param t the enum container_t type.
 * @return the new initialised htable.
 */
htable htable_new(int capacity, container_t t) {
    int i;
    htable result = emalloc (sizeof *result);
    result->capacity = capacity;
    result->count = 0;
    result->type = t;
    result->hashtable = emalloc(result->capacity *sizeof result->hashtable[0]);
    for (i = 0; i < result->capacity; i++) {
        result->hashtable[i] = NULL;
    }
    return result;
}

/**
 * Print out every non empty entry in the hashtable.
 * @param h the htable to print.
 * @param func(char *str) the print function to perform on each key.
 */
void htable_print(htable h, void func(char *str)) {
    int i;
    for (i = 0; i < h->capacity; i++) {
        if (h->hashtable[i] != NULL) {
            printf("%d:", i);
            container_print(h->hashtable[i], func);
            printf("\n");
        }
    }
}

/**
 * Search the hashtable for a key.
 * @param h the htable to search.
 * @param *str the string to search for.
 * @return 1 if found else 0.
 */
int htable_search(htable h, char *str) {
    unsigned int hashkey = htable_word_to_int(str);
    unsigned int position = (hashkey % h->capacity);

    if (h->hashtable[position] != NULL) {
        return container_search(h->hashtable[position], str);
    } else {
        return 0;
    }
}
