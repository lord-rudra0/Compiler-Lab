%{
    #include<stdio.h>
%}
KEYWORD (int|char|case|break|return|for|while|if|else)
DIGIT [0-9]+
ID [_a-zA-Z][a-zA-Z0-9]*
SPECCHAR [(){}[\]<>;,.#]
OP ">="|"<="|">"|"<"|"="|"+"|"-"|"*"|"/"
%%
{KEYWORD} {printf(" %s is a keyword \n",yytext);}
{DIGIT} {printf(" %s is a number \n",yytext);}
{SPECCHAR} {printf(" %s is a special character \n",yytext);}
{OP} {printf(" %s is a operator \n",yytext);}
[_a-zA-Z][a-zA-Z0-9]* {printf(" %s is a identifier \n",yytext);}
%%  
int main()
{
    yyin=fopen("expinput.txt", "r");

    if(yyin==NULL)
    {
        printf("Can not open the file");
    }

    else
    {
        printf("File is opened:");
        yylex();
    }

    fclose(yyin);
    return 0;
    
}

int yywrap()
{
    return 1;
}