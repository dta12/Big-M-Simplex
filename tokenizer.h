#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_EQUATIONS 10
#define MAX_VARIABLES 10
#define MAX_EQUATION_LENGTH 100

typedef struct term{
    /*
        Type of term we have in the tabelau
            'p'->objective function
            'c'->coefficient
            'x'->unassigned value in matrix
    */
    char type; 
    float value;
}s_term;

typedef struct tokens{
    int leq;
    int geq;
    int eq;
    char cmps[MAX_EQUATIONS][5];
    int num_rows;
    int num_cols;
    s_term **values;
}s_tokens;

s_tokens *initialize_token_object(s_tokens **tok);

void print_tokens(s_tokens *myTableau);

void tokenize(s_tokens* tok, int num_eqs, char eqs[MAX_EQUATIONS][MAX_EQUATION_LENGTH]);



