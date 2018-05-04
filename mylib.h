#ifndef MYLIB_H_
#define MYLIB_H_

#include <stddef.h>


/**
 * My Lib header file.
 * COSC242 Group Assignment, September 2017.
 * @author Daniela Lemow, Megan Seto and Nikolah Pearce.
 */ 

extern int getword(char *s, int limit, FILE *stream);
extern void *emalloc(size_t);
extern void *erealloc(void *, size_t);

#endif
