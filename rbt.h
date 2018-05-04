#ifndef RBT_H_
#define RBT_H_

/**
 * Red black tree header file.
 * COSC242 Group Assignment, September 2017.
 * @author Daniela Lemow, Megan Seto and Nikolah Pearce.
 */

typedef struct rbtnode *rbt;

extern rbt rbt_free(rbt r);
extern rbt rbt_insert(rbt r, char *str);
extern rbt rbt_new();
extern void rbt_preorder(rbt r, void f(char *str));
extern int rbt_search(rbt r, char *str);

#endif
 
