#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EQUATIONS 10
#define MAX_VARIABLES 10
#define MAX_TERM_LENGTH 20

typedef struct simplex_term{
    bool artifical;
    bool slack;
    float value;
}s_term;


void parseEquation(char *eq) {
    int entry;
    char *token;
    token = strtok(eq, " ");
    while(token != NULL){
        if(sscanf(token, "%d%*c", &entry) == 1){
            printf("%d\n", entry);
        }
        token = strtok(NULL, " ");
    }
}

int main() {
    char inputEquations[MAX_EQUATIONS][100];

    // Example: Input equations
    strcpy(inputEquations[0], "2x + 3y - z = 5");
    strcpy(inputEquations[1], "4x - y + 2z = 10");
    strcpy(inputEquations[2], "x + y + z = 7");

    // Parse each equation
    for (int i = 0; i < 3; i++) {
        parseEquation(inputEquations[i]);
    }


    return 0;
}
