#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>

typedef struct cell_val_options_t{
    int n;
    int vals[9];
} cell_val_options_t;


int solve(int * sudoku, int empty_cells);
int find_possible_entries(int * sudoku, int * empty_cells);
int find_options_helper(int r, int c, int * sudoku, cell_val_options_t * options);



#endif
