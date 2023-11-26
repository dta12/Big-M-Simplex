#include "tokenizer.h"

#define MAX_FORM_WIDTH 100

// 10^9
#define M_VALUE 1000000//1000000000

typedef struct cell {
    /*
        Type of term we have in the tabelau
            'c'->coefficient
            'm'->M term variable
        
        Note that any operation that involved M will convert coefficient types to 'm' types
    */
    char type;
    char symbolic_form[MAX_FORM_WIDTH];
    float value;
}s_cell;

typedef struct tableau{
    bool is_finished;
    bool contains_artificals;
    float objective_p;
    int num_rows;
    int num_cols;
    s_cell **table;
}s_tableau;

s_tableau *initialize_tabelau_object(s_tableau **table);

void swap_cells(s_tableau *table, int r, int c1, int c2);

void fill_tabelau(s_tableau *table, s_tokens* tok);

void print_tabelau(s_tableau *table);
