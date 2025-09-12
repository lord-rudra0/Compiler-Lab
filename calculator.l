%{
#include "y.tab.h"
#include <stdio.h>
%}

[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[ \t\n]+    ;
\+          return PLUS;
-           return MINUS;
\*          return TIMES;
/           return DIVIDE;
\(          return LPAREN;
\)          return RPAREN;
.           return yytext[0];
%%
