#include "simplex.h"

s_table *initialize_table_object(s_table **table){
    (*table) = (s_table*)calloc(1, sizeof(s_table));
    (*table)->table = (s_cell **)calloc(1, MAX_EQUATIONS*sizeof(s_cell *));
    for(int i = 0; i < MAX_EQUATIONS; i++){
        (*table)->table[i] = (s_cell *)calloc(1, MAX_VARIABLES*sizeof(s_cell));
    }
    return (*table);
}

void swap_cells(s_table *table, int r, int c1, int c2){
    s_cell t = table->table[r][c1];
    table->table[r][c1].value = table->table[r][c2].value;
    table->table[r][c2].value = t.value;
}

void fill_tabelau(s_table *table, s_tokens* tok){
    table->num_rows = tok->num_rows;
    table->num_cols = tok->num_cols + tok->leq + 2*tok->geq;
    int p_loc = -1;     // location of the objective variable in the row if it has one 
    int s_counter = 0;  // counter for artifical variables
    int a_counter = 0;  // counter for slack variables

    int i;
    for (i = 0; i < tok->num_rows; ++i) {
        int count_assigned = 0;
        int j;
        for (j = 0; j < tok->num_cols; ++j) {
            //printf("%c %.1f\n", tok->values[i][j].type, tok->values[i][j].value);
            table->table[i][j].value = tok->values[i][j].value;
            char t = tok->values[i][j].type;
            if(t == 'c') count_assigned++;
            if(t == 'p') p_loc = j;
        }
        //move the last coefficient tokens to the end of the matrix
        if(p_loc == -1){    
            swap_cells(table, i, count_assigned - 1, table->num_cols - 1);
        }else{
            swap_cells(table, i, p_loc, table->num_cols - 2);
            swap_cells(table, i, p_loc+1, table->num_cols - 1);
        }
        // introduce slack variable only
        if(strcmp(tok->cmps[i], "<=") == 0){
            table->table[i][(count_assigned - 1) + s_counter].value = 1;
            s_counter++;
        }
        // introduce slack variable and artifical variable
        if(strcmp(tok->cmps[i], ">=") == 0){   
            table->table[i][(count_assigned - 1) + s_counter].value = -1;
            s_counter++;
            table->table[i][(count_assigned - 1) + s_counter + a_counter].value = 1;
            a_counter++;
        }
        count_assigned = 0;
    }
    table->objective_p = table->table[table->num_rows - 1][table->num_cols - 1].value;
}

void print_tabelau(s_table *table){
    for (int i = 0; i < table->num_rows; ++i) {
        for (int j = 0; j < table->num_cols; ++j) {
            printf("%.1f\t", table->table[i][j].value);
        }
        printf("\n");
    }
    printf("MAX P = %f", table->objective_p);
}

int main() {
    char inputEquations[MAX_EQUATIONS][100];

    // Example: Input equations
    strcpy(inputEquations[0], "x + y <= 10");
    strcpy(inputEquations[1], "-x + y >= 2");
    strcpy(inputEquations[2], "-2x - y + p = 5");
    s_tokens *tokens;
    initialize_token_object(&tokens);
    tokenize(tokens, 3, inputEquations);
    //print_tokens(tokens);

    s_table *table;
    initialize_table_object(&table);
    fill_tabelau(table, tokens);
    print_tabelau(table);

    return 0;
}