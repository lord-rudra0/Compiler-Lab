%{
    #include<stdio.h>
    #include"y.tab.h"
    #include<stdlib.h>
    extern int yylex(void);
    void yyerror(const char*msg);
%}

%token DIGIT LETTER
%left "+" "-"
%left "*" "/"
%right UMINUS

%%
input : expr {printf("valid expr") ;exit(0);};

expr:expr "+" expr|
    expr "-" expr|
    expr "*" expr|
    expr "/" expr|
    "-" expr %prec UMINUS|
    "(" expr ")"|
    LETTER|
    DIGIT
%%

int main()
{
    printf("Enter the Exp: ");
    yyparse();
}

void yyerror(const char*msg)
{
    printf("Error %s",msg);
}
