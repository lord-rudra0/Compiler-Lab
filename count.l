%{
    int cline;
    int cwords;
    int cchar;
%}

CHARACTER [a-zA-Z]
WORD [a-zA-Z]+
LINE [^\n]*

%%
\n          { cline++; }                // count lines
[ \t]+      { /* skip whitespace */ }   // skip whitespace
[a-zA-Z]+   { cwords++; cchar += yyleng; } // count words and count their letters
.           { cchar++; }                // any other character is a character
%%

//%%
//{LINE} {
  //  cline++;
//}
//{WORD} {
  //  cwords++;
//}
//{CHARACTER} {
  //  cchar++;
//}
//%%


int main() {
    cline = 0;
    cwords = 0;
    cchar = 0;

    printf("Enter text (Ctrl+D to end):\n");
    yylex();

    printf("Lines: %d\n", cline);
    printf("Words: %d\n", cwords);
    printf("Characters: %d\n", cchar);
    
    return 0;
}

int yywrap() {
    return 1;
}
