#ifndef HTABLE_H_
#define HTABLE_H_

#include <stdio.h>
#include "container.h"

/**
 * Htable header file.
 * COSC242 Group Assignment, September 2017.
 * @author Daniela Lemow, Megan Seto and Nikolah Pearce.
 */ 
 
typedef struct htablerec *htable;

extern void htable_free(htable h);
extern int htable_insert(htable h, char *str);
extern htable htable_new(int capacity, container_t t);
extern void htable_print(htable h, void func(char *str));
extern int htable_search(htable h, char *str);

#endif
