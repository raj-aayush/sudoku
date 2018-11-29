#include "header.h"
#include "external.h"
#include <time.h>

int main(){
  clock_t begin;
  clock_t end;
  for(int i = 1; i < 6; i++){
    printf("Test Case %d\n", i);
    int sudoku[9*9] = { 0 };
    int empty_cells = get_sudoku(sudoku, i);

    begin = clock();
    solve(sudoku, empty_cells);
    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    test_print_sudoku(sudoku, i);
    printf("Run time: %0.4f\n", time_spent);
  }

  return 0;
}

int solve(int * sudoku, int empty_cells){
    int i = 0;
    int scary_sudoku = 0;
    while(empty_cells > 0 && scary_sudoku == 0){
      printf("Iteration %d -----------------------------------------------------\n", i);
      printf("Num of empty cells: %d\n", empty_cells);
      // test_print_sudoku(sudoku);
      scary_sudoku = find_possible_entries(sudoku, &empty_cells);
      i++;
    }
    return 0;
}

int find_possible_entries(int * sudoku, int * empty_cells){
    int scary_sudoku = 1;
    cell_val_options_t empty_struct_cell_val;
    empty_struct_cell_val.n = 0;
    for(int i = 0; i < 9; i++) empty_struct_cell_val.vals[i] = 0;
    cell_val_options_t options_array[9*9] = { empty_struct_cell_val };

    //Go through each row and look for empty cells
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(sudoku[i*9+j] != 0) continue;
            find_options_helper(i, j, sudoku, options_array);
            if(options_array[i*9+j].n == 1){
              scary_sudoku = 0;
              sudoku[i*9+j] = options_array[i*9+j].vals[0];
              (*empty_cells)--;
            }
        }
    }
    if(scary_sudoku == 1) printf("Can't solve this sudoku\n");
    return scary_sudoku;
}

int find_options_helper(int r, int c, int * sudoku, cell_val_options_t * options){
    int blk = (r/3)*3 + c/3;
    int start_c = (blk%3)*3;
    int start_r = (blk/3)*3;

    int temp_arr[10] = { 0 };
    int ind1 = 0;
    int ind2 = 0;
    int ind3 = 0;
    //Check the row, col and blk
    for(int i = 0; i < 9; i++){
      ind1 = i*9+c;
      ind2 = r*9+i;
      ind3 = (start_r+i/3)*9+start_c+i%3;
      if(sudoku[ind1] != 0) temp_arr[sudoku[ind1]] = 1;
      if(sudoku[ind2] != 0) temp_arr[sudoku[ind2]] = 1;
      if(sudoku[ind3] != 0) temp_arr[sudoku[ind3]] = 1;
    }
    for(int i = 1; i < 10; i++){
      if(temp_arr[i] == 0){
        options[r*9+c].vals[options[r*9+c].n] = i;
        options[r*9+c].n++;
      }
    }
    return 0;
}
