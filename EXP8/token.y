%{
    #include<stdio.h>
    #include"y.tab.h"
    #include<string.h>
    #include<stdlib.h>

    int yylex(void);
    void yyerror(const char*msg);
%}

%token IDENTIFIER

%%
input:IDENTIFIER {printf("\n Valid IDENTIFIER");}
| {printf("\n InValid IDENTIFIER");}
%%


int main()
{
    printf("Enter the IDENTIFIER: ");
    yyparse();
}

void yyerror(const char *msg)
{
    printf("Error: %s",msg);
}