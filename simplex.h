#include "tokenizer.h"

typedef struct cell {
    char type;
    char *symbolic_form;
    float value;
}s_cell;

typedef struct table{
    bool is_finished;
    float objective_p;
    int num_rows;
    int num_cols;
    s_cell **table;
}s_table;

s_table *initialize_table_object(s_table **table);

void swap_cells(s_table *table, int r, int c1, int c2);

void fill_tabelau(s_table *table, s_tokens* tok);

void print_tabelau(s_table *table);
