#include "simplex.h"

s_table *initialize_table_object(s_table **table){
    (*table) = (s_table*)calloc(1, sizeof(s_table));
    (*table)->table = (s_cell **)calloc(1, MAX_EQUATIONS*sizeof(s_cell *));
    for(int i = 0; i < MAX_EQUATIONS; i++){
        (*table)->table[i] = (s_cell *)calloc(1, MAX_VARIABLES*sizeof(s_cell));
    }
    return (*table);
}

void fill_tabelau(s_table *table, s_tokens* tok){
    table->num_rows = tok->num_rows;
    table->num_cols = tok->num_cols + tok->leq + 2*tok->geq;
    int p_loc = -1;
    for (int i = 0; i < tok->num_rows; ++i) {
        int count_assigned = 0;
        for (int j = 0; j < tok->num_cols; ++j) {
            //printf("%c %.1f\n", tok->values[i][j].type, tok->values[i][j].value);
            table->table[i][j].value = tok->values[i][j].value;
            char t = tok->values[i][j].type;
            if(t == 'c') count_assigned++;
            if(t == 'p') p_loc = j;
        }
        //move the last coefficient tokens to the end of the matrix
        if(p_loc == -1){    
            s_term t = tok->values[i][count_assigned - 1];
            table->table[i][count_assigned - 1].value = 0.0;
            table->table[i][table->num_cols - 1].value = t.value;
        }else{
            s_term t = tok->values[i][p_loc];
            table->table[i][p_loc].value = 0.0;
            table->table[i][table->num_cols - 2].value = t.value;
            t = tok->values[i][p_loc+1];
            table->table[i][p_loc+1].value = 0.0;
            table->table[i][table->num_cols - 1].value = t.value;
        }
        count_assigned = 0;
    }
}

void print_tabelau(s_table *table){
    for (int i = 0; i < table->num_rows; ++i) {
        for (int j = 0; j < table->num_cols; ++j) {
            printf("(%.1f)\t", table->table[i][j].value);
        }
        printf("\n");
    }
}

int main() {
    char inputEquations[MAX_EQUATIONS][100];

    // Example: Input equations
    strcpy(inputEquations[0], "x + y <= 10");
    strcpy(inputEquations[1], "-x + y >= 2");
    strcpy(inputEquations[2], "-2x - y + p = 0");
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