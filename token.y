%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
void yyerror(const char *s);
%}

%token LETTER DIGIT

%%
id: L { printf("Valid Identifier\n"); exit(0); }

L:  LETTER
    | L LETTER
    | L DIGIT
    ;
%%

int main() {
        printf("Enter the variable name:\n");
        yyparse();
        return 0;
}

void yyerror(const char *s) {
        printf("Invalid Identifier\n");
}