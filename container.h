#ifndef CONTAINER_H_
#define CONTAINER_H_

/**
 * Container header file.
 * COSC242 Group Assignment, September 2017.
 * @author Daniela Lemow, Megan Seto and Nikolah Pearce.
 */
 
typedef enum container_e {
    FLEX_ARRAY,
    RED_BLACK_TREE
} container_t;

typedef struct containerrec *container;

extern void container_add(container c, char *str);
extern void container_free(container c);
extern container container_new(container_t t);
extern void container_print(container c, void func(char *str));
extern int container_search(container c, char *str);

#endif
