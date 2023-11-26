#include <stdio.h>
#include "tabelau.h"
#include "float.h"

// to make things pretty 

void print_line(int width, char separator) {
    for (int i = 0; i < width; i++) {
        printf("%c", separator);
    }
    printf("\n");
}

/*
    - return -1 if no pivot column can be found
    otherwise return the column index of the entry with minimum value
    - no pivot column can be found if all of the objective function entries are >= 0
*/
int find_pivot_col(s_tableau *table){
    float min_val = 0;
    int curr_index = -1;
    for (int i = 0; i < table->num_cols - 1; i++){
        s_cell temp = table->table[table->num_rows - 1][i];
        if(temp.value < min_val){
            min_val = temp.value;
            curr_index = i;
        }
    }
    return curr_index;
}

/*
    - assumes a pivot column is already found 
    - return -1 if no pivot row can be found
    otherwise return the row index of the entry with smallest positive ratio as the pivot
    - if there are no positive elements for that column, then no optimmal solution exists and feasible region is unbounded.
*/
int find_pivot_row(s_tableau *table, int c){
    float min_ratio = FLT_MAX;
    int curr_index = -1;
    for (int i = 0; i < table->num_rows - 1; i++){
        s_cell curr_row_entry = table->table[i][c];
        s_cell last_row_entry = table->table[i][table->num_cols - 1];
        float ratio = last_row_entry.value/curr_row_entry.value;
        if(ratio > 0 && ratio < min_ratio){
            min_ratio = ratio;
            curr_index = i;
        }
    }
    return curr_index;
}

void apply_pivot(s_tableau *table, int r, int c){
    // Divide the pivot row by the pivot element
    float pivot_element = table->table[r][c].value;
    for (int i = 0; i < table->num_cols; i++) {
        table->table[r][i].value /= pivot_element;
    }

    // Perform row operations to make other elements in the pivot column zero
    for (int i = 0; i < table->num_rows; i++) {
        if (i != r) {
            float factor = -table->table[i][c].value;
            for (int j = 0; j < table->num_cols; ++j) {
                table->table[i][j].value += factor * table->table[r][j].value;
            }
        }
    }
    // update the max value
    table->objective_p = table->table[table->num_rows - 1][table->num_cols - 1].value;
}

void apply_simplex(s_tableau *table){
    int iteration = 0;
    printf("%s\n", "Initial Tabelau:");
    while(!table->is_finished){
        print_tabelau(table);
        print_line(8*table->num_cols, '-');
        int piv_col = find_pivot_col(table);
        if(piv_col == -1){
            printf("%s\n", "The optimal solution has been found");
            table->is_finished = true;
            print_tabelau(table);
        }else{
            int piv_row = find_pivot_row(table, piv_col);
            if(piv_row == -1){
                printf("%s\n", "No optimal solution exists");
                table->is_finished = true;
                print_tabelau(table);
            }
            apply_pivot(table, piv_row, piv_col);
            iteration++;
            printf("Iteration: %d \tPivot chosen: (r: %d, c: %d)\n", iteration, piv_row + 1, piv_col + 1);
        }
    }
}

int main() {
    char equations[MAX_EQUATIONS][100];

    FILE *f = fopen("eq.txt", "r");

    if(f == NULL){
        perror("Error opening the equation file");
        return 1;
    }
    char buffer[100];
    int counter = 0;
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        // Process each equation/inequality line by line
        strcpy(equations[counter], buffer);
        counter++;
    }
    
    // setup the token object
    s_tokens *tokens;
    initialize_token_object(&tokens);
    tokenize(tokens, 3, equations);

    // setup the tabelau
    s_tableau *table;
    initialize_tabelau_object(&table);
    fill_tabelau(table, tokens);

    // apply the simplex method to solve
    apply_simplex(table);
    return 0;
}