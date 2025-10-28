%{
    #include<stdio.h>
    #include<stdlib.h>
    #include"y.tab.h"  
    void yyerror(const char*msg);
    int yylex(void);
%}
%token DIGIT
%left '+' '-'
%left '*' '/'
%right UMINUS
%%
calc:expr {printf("result is %d: ",$1);};
expr:
DIGIT {$$=$1;}|
expr '+' expr {$$=$1+$3;}|
expr '-' expr {$$=$1+$3;}|
expr '*' expr {$$=$1+$3;}|
expr '/' expr {
    if($3==0)
    {
        yyerror("divider by zero");
        $$=0;
    }

    else
    {
        $$=$1/$3;
    }
}
;
%%

int main()
{
    printf("Enter the Exp : ");
    yyparse();
}

void yyerror(const char*msg) {
    printf("Error : %s",msg);

}