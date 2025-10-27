%%
[0-9]*[02468]  {printf("it is Even number");}
[0-9]*[13579]  {printf("it is Odd number");}
%%

int main()
{
    printf("Enter the number \t");
    yylex();
}

int yywrap()
{
    return 1;
}