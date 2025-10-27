%{
    #include<stdio.h>
    #include "y.tab.h"

%}

%%
[a-zA-Z]+[a-zA-Z0-9] {return IDENTIFIER;}
%%

int yywrap()
{
    return 1;
}