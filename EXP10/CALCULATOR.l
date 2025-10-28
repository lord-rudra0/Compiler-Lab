%{
    #include<stdio.h>
    #include<stdlib.h>
    #include"y.tab.h" 
    extern int yylval;   
%}

%%
[0-9]+ {yylval=atoi(yytext); return DIGIT;}
. {return yytext[0];}
\n ;
%%

int yywrap()
{
    return 1;
}