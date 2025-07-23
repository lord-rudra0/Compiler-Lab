DIGIT [0-9]
%%

{DIGIT}+ {
    { if (atoi(yytext) % 2 == 0) {
            printf("Even: %s\n", yytext);
        } else {
            printf("Odd: %s\n", yytext);
        }
  }
}
%%

int main() {
    printf("Enter numbers (Ctrl+D to end):\n");
    yylex();
    return 0;
}
int yywrap() {
    return 1;
}
    