%{
    #include<stdio.h>
    int isvalid = 0;

%}

%%
[a-z0-9]+@[a-z]+.[a-z] {isvalid=1;}
%%

int main()
{
    printf("Enter Mail: ");
    yylex();

    if(isvalid)
    {
        printf("Mail is valid");
    }
    else{
        printf("Mail is invalid");
    }
}

int yywrap()
{
    return 1;
}
