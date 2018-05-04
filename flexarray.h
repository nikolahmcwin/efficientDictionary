#ifndef FLEXARRAY_H_
#define FLEXARRAY_H_

/**
 * Flexarray header file.
 * COSC242 Group Assignment, September 2017.
 * @author Daniela Lemow, Megan Seto and Nikolah Pearce.
 */
 
typedef struct flexarrayrec *flexarray;
 
extern void flexarray_append(flexarray f, char *str);
extern void flexarray_free(flexarray f);
extern int flexarray_is_present(flexarray f, char *str);
extern flexarray flexarray_new();
extern void flexarray_visit(flexarray f, void func(char *str));

#endif
