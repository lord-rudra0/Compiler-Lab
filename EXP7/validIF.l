%{
    int isvalid=0;
    int validIf=0;
%}

%%
if[ \t]*\([ \t]*[A-Za-z0-9_!=<>+\-*/%&|^ ]+[ \t]*\) {isvalid=1;validIf++;}
%%

int main()
{
    FILE*fp;
    fp=fopen("expinput.txt","r");

    if(fp==NULL)
    {
        printf("error");
    }
    else
    {
        yyin=fp;
        yylex();

        if(isvalid)
        {
            printf("there are %d valid if",validIf);
        }
        else
        {
            printf("No valid IF");
        }
    }

    return 0;
}


int yywrap()
{
    return 1;
}