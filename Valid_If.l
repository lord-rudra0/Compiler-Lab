%{
int valid_if_count = 0;
int if_stack = 0;
%}

%%
"if"[ \t]*"("[^)]*")"[ \t]*"{"    { valid_if_count++; if_stack++; }
"}"                             { if(if_stack > 0) if_stack--; }
.|\n                            { /* ignore other characters */ }
%%

int main() {
    printf("Enter a C program:\n");
    yylex();
    printf("Number of valid if statements: %d\n", valid_if_count);
    printf("Number of unmatched if statements: %d\n", if_stack);
    return 0;
}

int yywrap() {
    return 1;
}