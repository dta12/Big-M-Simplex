#include "tabelau.h"
#include "float.h"
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
    for (int i = 0; i < table->num_rows; i++) {
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
}

int main() {
    char equations[MAX_EQUATIONS][100];

    // Example: Input equations
    strcpy(equations[0], "x + y <= 10");
    strcpy(equations[1], "-x + y >= 2");
    strcpy(equations[2], "-2x - y + p = 0");
    s_tokens *tokens;
    initialize_token_object(&tokens);
    tokenize(tokens, 3, equations);
    //print_tokens(tokens);

    s_tableau *table;
    initialize_tabelau_object(&table);
    fill_tabelau(table, tokens);
    print_tabelau(table);
    apply_pivot(table, 1, 0);
    print_tabelau(table);
    return 0;
}