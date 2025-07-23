DIGIT [0-9]
ID [a-zA-Z_][a-zA-Z0-9_]*
KEYWORD (if|else|while|return|int|float|char|void)
OPERATOR ">"|"<"|"="|"<="|">="|"+"|"-"|"/"|"*"
SPECIALCHARACTER "("|")"|""|""|"["|"]"|"."|";"|","
%%
{KEYWORD}+ {printf("Keyword: %s\n", yytext);}
{OPERATOR}+ {printf("Operator: %s\n", yytext);}
{SPECIALCHARACTER}+ {printf("Special Character: %s\n", yytext);}
{DIGIT}+ {printf("Digit: %s\n", yytext);}
{ID}+ {printf("Identifier: %s\n", yytext);}
%%

void main()
{
    printf("Enter the code\n");
    yylex();

    
}

int yywrap() {
    return 1;
}