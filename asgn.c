#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <time.h>
#include "mylib.h"
#include "htable.h"

/**
 * Main program for creating and testing our hashtable.
 * Takes command line arguments and performs on them.
 * COSC242 Group Assignment, September 2017.
 * @author Daniela Lemow, Megan Seto and Nikolah Pearce.
 */
 
#define DEFAULT_SIZE 3877

/**
 * Prints a string to stdout.
 * @param *s the string to be printed.
 */
void print_key(char *s) {
    printf(" %s", s);
}

int main(int argc, char **argv) {

    htable h;
    char word[256];
    int size = DEFAULT_SIZE;
    FILE *dictionary_words;
    
    container_t type = FLEX_ARRAY;
    int print = 0; /* do not print automatically */
    int print_info = 0; /* do not print timing info automatically */    
    int unknown_words = 0;
    
    clock_t start_fill, end_fill, start_search, end_search;
    double time_to_fill, time_to_search;
    
    const char *optstring = "rs:pih";
    char option;

    while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
            case 'r':
                /* Use robust chaining */
                type = RED_BLACK_TREE;
                break;
            case 's': 
                /* Use parameter to set size of the hash table */
                size = atoi(optarg);
                fprintf(stderr, "Size: %d \n", size);
                break;
            case 'p':
                /* Print hash table to stdout by setting print to true */
                print = 1;
                break;
            case 'i':
                /* Print timing info by setting print_info to true */
                print_info = 1;
                break;
            case 'h':
            default:
                fprintf(stderr, "Usage: [filename] [args]\n");
                fprintf(stderr, "Enter -r for robust chaining.\n");
                fprintf(stderr, "Enter -s then an int to set table size.\n");
                fprintf(stderr, "Enter -p to print the hashtable.\n");
                fprintf(stderr, "Enter -i to print timing information.\n");
                fprintf(stderr, "Required: [filename] to read words from.\n");
                exit(EXIT_FAILURE);
        }
    }
    
    /* Fill dictionary hash table via command line file name */
    if (NULL == (dictionary_words = fopen(argv[optind], "r"))) {
        fprintf(stderr, "Could not open file. Execution aborted.\n");
        exit(EXIT_FAILURE);
    } else {
        start_fill = clock();
        h = htable_new(size, type);
        while(getword(word, sizeof word, dictionary_words) != EOF) {
            htable_insert(h, word);
        }
        fclose(dictionary_words);
        end_fill = clock();
        time_to_fill = (end_fill - start_fill) / (double) CLOCKS_PER_SEC;
    }

    /* Either print or read words in from stdin, checking against dictionary */
    if (print) {
        htable_print(h, print_key);
    } else {
        start_search = clock();
        while (getword(word, sizeof word, stdin) != EOF) {
            if (htable_search(h, word) == 0) {
                printf("%s\n", word);
                unknown_words++;
            }
        }
        end_search = clock();
        time_to_search = (end_search - start_search) / (double) CLOCKS_PER_SEC;

        if (print_info) {
            fprintf(stderr, "Fill time : %f\n", time_to_fill);
            fprintf(stderr, "Search time : %f\n", time_to_search);
            fprintf(stderr, "Unknown words : %d\n", unknown_words);
        }
    }
    
    htable_free(h);
    return EXIT_SUCCESS;
    
}
