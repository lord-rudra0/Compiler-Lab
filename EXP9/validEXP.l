%{
    #include<stdio.h>
    #include<stdlib.h>
    #include"y.tab.h"
    extern int yylval;
    
%}

%%
[0-9]+ {yylval=atoi(yytext);return DIGIT;}
[_a-zA-Z][_a-zA-Z0-9]* {return LETTER;}
"+" { return '+'; }
"-" { return '-'; }
"*" { return '*'; }
"/" { return '/'; }
"(" { return '('; }
")" { return ')'; }
\n {return 0;}
[\t] {;}
. {return yytext[0];}

%%



int yywrap()
{
    return 1;
}