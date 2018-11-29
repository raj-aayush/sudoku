#include "external.h"

int given_values[9*9] = { 0 };

int get_sudoku(int * su, int n){
  int empty = 0;

   char ch;
   FILE *fptr;

   char file_name[50];
   sprintf(file_name, "test%d.txt", n);
   if ((fptr = fopen(file_name,"r")) == NULL){
       printf("Error! opening file\n");
       exit(1);
   }
    int val = 0;
    for(int i = 0; i < 9; i++){
      for(int j = 0; j < 9; j++){
        if((ch = fgetc(fptr)) == EOF){
          i = 10;
          break;
        }
        val = ch - '0';
        if(val == 0) empty++;
        if(val != 0) given_values[i*9+j] = 1;
        else given_values[i*9+j] = 0;
        su[i*9+j] = val;
      }
    }
    fclose(fptr);
    return empty;
}

int test_print_sudoku(int * test_maze, int n){
    int invalid_entries[9*9] = { 0 };
    print_maze(test_maze, invalid_entries);
    char ch;
    FILE *fptr;
    char file_name[50];
    sprintf(file_name, "sol%d.txt", n);
    if ((fptr = fopen(file_name,"r")) == NULL){
        printf("Error! opening file\n");
        exit(1);
    }
    int val = 0;
    int matches_solution = 1;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if((ch = fgetc(fptr)) == EOF){
                i = 10;
                break;
            }
            val = ch - '0';
            if(test_maze[i*9+j] != val) matches_solution = 0;
        }
    }
    int maze_valid = is_maze_valid(test_maze, invalid_entries);
    if(maze_valid == 1){
        printf(GRN "VALID MAZE\n" RESET);
    }
    else{
        printf(RED "INVALID MAZE\n" RESET);
    }
    if(matches_solution == 1){
        printf(GRN "MATCHED SOLUTION\n" RESET);
    }
    else{
        printf(RED "DIDNT MATCH SOLUTION\n" RESET);
    }
    if(matches_solution == 1 && maze_valid == 1){
        printf(GRN "PASSED TEST %d =========================================\n" RESET, n);
    }
    else{
        printf(RED "FAILED TEST %d ========================================\n" RESET, n);
    }
    fclose(fptr);
    return 0;
}

int print_maze(int * maze, int * invalid){
  for(int i = 0; i < 19; i++){
      for(int j = 0; j < 9; j++){
          //Even rows are just to draw the maze
          if(i%2 == 0){
              //Different figures for every 3rd row
              if(i%6 == 0){
                  if(j == 0) printf("|===");
                  else printf("====");
              }
              else{
                  if(j == 0) printf("|---");
                  else printf("----");
              }
          }
          //Odd rows that include numbers
          else{
              //0 values represent spaces
              if(maze[(i/2)*9 + j] == 0) printf("|   ");
              else{
                if(given_values[(i/2)*9+j] == 1 && invalid[(i/2)*9 + j] == 1)
                    printf("|"YEL " %d " RESET, maze[(i/2)*9 + j]);
                else if(given_values[(i/2)*9+j] == 1)
                    printf("|"BLU " %d " RESET, maze[(i/2)*9 + j]);
                else if(invalid[(i/2)*9 + j] == 1)
                    printf("|"RED " %d " RESET, maze[(i/2)*9 + j]);
                else printf("| %d ", maze[(i/2)*9 + j]);
              }
          }
    }
    //Last character for each row
    printf("|\n");
  }
  return 0;
}

int is_maze_valid(int * maze, int * invalid){
  int validity = 0;
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      if(maze[i*9+j] == 0) continue;
      validity += check_row(i, maze[i*9+j], maze, invalid);
      validity += check_col(j, maze[i*9+j], maze, invalid);
      validity += check_blk(i, j, maze[i*9+j], maze, invalid);
    }
  }
  return (validity == 0)? 1: 0;
}

int check_row(int row, int val, int * maze, int * invalid){
  int count = 0;
  for(int i = 0; i < 9; i++){
    if(maze[row*9+i] == val) count++;
  }
  if(count > 1){
    for(int i = 0; i < 9; i++){
      if(maze[row*9+i] == val) invalid[row*9+i] = 1;
    }
  }
  // if(count > 1) printf("Row %d\n", row);
  return (count > 1)? -1: 0;
}

int check_col(int col, int val, int * maze, int * invalid){
  int count = 0;
  for(int i = 0; i < 9; i++){
    if(maze[i*9+col] == val) count++;
  }
  if(count > 1){
    for(int i = 0; i < 9; i++){
      if(maze[i*9+col] == val) invalid[i*9+col] = 1;
    }
  }
  // if(count > 1) printf("Col %d\n", col);
  return (count > 1)? -1: 0;
}

int check_blk(int row, int col, int val, int * maze, int * invalid){
  int blk = (row/3)*3 + col/3;
  int start_c = (blk%3)*3;
  int start_r = (blk/3)*3;
  int count = 0;
  for(int i = start_r; i < start_r+3; i++){
    for(int j = start_c; j < start_c+3; j++){
      if(maze[i*9+j] == val) count++;
    }
  }
  if(count > 1){
    for(int i = start_r; i < start_r+3; i++){
      for(int j = start_c; j < start_c+3; j++){
        if(maze[i*9+j] == val) invalid[i*9+j] = 1;
      }
    }
  }
  // if(count > 1) printf("Blk %d\n", blk);
  return (count > 1)? -1: 0;
}
