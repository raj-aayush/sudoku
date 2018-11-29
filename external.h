#ifndef EXTERN_H
#define EXTERN_H

#include <stdio.h>
#include <stdlib.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

int get_sudoku(int * su, int n);
int test_print_sudoku(int * test_maze, int n);
int print_maze(int * maze, int * invalid);
int is_maze_valid(int * maze, int * invalid);
int check_row(int row, int val, int * maze, int * invalid);
int check_col(int col, int val, int * maze, int * invalid);
int check_blk(int row, int col, int val, int * maze, int * invalid);

#endif
