lex program of valid gmail ID

%{
   int valid = 0;
%}

%%
[@.] { valid = 1; }
%%

int main() {
    printf("Enter a Gmail Id:");
    yylex();
    if (valid) {
        printf("Valid Gmail ID\n");
    } else {
        printf("Invalid Gmail ID\n");
    }
    return 0;
}

int yywrap() {
    return 1;
}