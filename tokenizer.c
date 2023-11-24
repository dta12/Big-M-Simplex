#include "tokenizer.h"

s_tokens *initialize_token_object(s_tokens **tok){
    (*tok) = (s_tokens*)calloc(1, sizeof(s_tokens));
    (*tok)->values = (s_term **)calloc(1, MAX_EQUATIONS*sizeof(s_term *));
    for(int i = 0; i < MAX_EQUATIONS; i++){
        (*tok)->values[i] = (s_term *)calloc(1, MAX_VARIABLES*sizeof(s_term));
    }

    return (*tok);
}

void print_tokens(s_tokens *tok) {
    printf("=:%d\t>=:%d\t<=:%d\t\n", tok->eq, tok->geq, tok->leq);
    for (int i = 0; i < tok->num_rows; i++) {
        for (int j = 0; j < tok->num_cols; j++) {
            printf("(%c, %.1f)\t", tok->values[i][j].type,tok->values[i][j].value);
        }
        printf("cmp: %s\n", tok->cmps[i]);
    }
}

void tokenize(s_tokens* tok, int num_eqs, char eqs[MAX_EQUATIONS][MAX_EQUATION_LENGTH]) {
    int row = 0;
    int max_col = 0;
    int cmp_counter = 0;
    while(row < num_eqs){
        int col = 0;
        float entry;
        bool neg_flag = false;
        char *token;
        token = strtok(eqs[row], " ");
        while(token != NULL){
            if(strcmp(token, "+") == 0){
                // don't do anythging for this case
            }else if(strcmp(token, "=") == 0){
                tok->eq++;
                strcpy(tok->cmps[cmp_counter], token);
                cmp_counter++;
            }else if(strcmp(token, "-") == 0){
                neg_flag = true;
            }else if(token[0] == '-'&& strlen(token) == 2 
                                    && isalpha(token[1]) != 0){
                // weird edge case to handle where we have '-x' or '-y'
                entry = -1;
                tok->values[row][col].value = entry;
                tok->values[row][col].type = 'c';
                col++;
            }else if(sscanf(token, "%f%*c", &entry) == 1){
                if(neg_flag){
                    entry = -entry;
                    neg_flag = false;
                }
                tok->values[row][col].value = entry;
                tok->values[row][col].type = 'c';
                col++;
            }else if(sscanf(token, "%[a-zA-Z]") == 1){
                entry = 1;
                if(neg_flag){
                    entry = -entry;
                    neg_flag = false;
                }
                tok->values[row][col].value = entry;
                tok->values[row][col].type = 'c';
                if(token[0] == 'p'){
                    tok->values[row][col].type = 'p';
                }
                col++;
            }else{
                int leq = strcmp(token, "<=");
                int geq = strcmp(token, ">=");
                if(leq == 0) {
                    tok->leq++; 
                    strcpy(tok->cmps[cmp_counter], token);
                    cmp_counter++;
                }
                if(geq == 0) {
                    tok->geq++; 
                    strcpy(tok->cmps[cmp_counter], token);
                    cmp_counter++;
                }
                // unrecognized token
                if(leq != 0 && geq != 0) printf("unrecongized token: %s\n", token);
            }

            token = strtok(NULL, " ");
        }
        if(col > max_col){
            max_col = col;
            col = 0;
        }
        row++;
    }
    tok->num_cols = max_col;
    tok->num_rows = row;
    //assign default
    for (int i = 0; i < tok->num_rows; i++) {
        for (int j = 0; j < tok->num_cols; j++) {
            char t = tok->values[i][j].type;
            if(t != 'c' && t != 'p') tok->values[i][j].type = 'x';
        }
    }
}

