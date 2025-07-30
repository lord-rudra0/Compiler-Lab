%{
    int print=0;
    int scan=0;
%}

%%
"printf" { print++; printf("writef"); }
"scanf" { scan++; printf("readf"); }
%%


int main(){
    printf("Enter a C program:\n");
    yylex();
    printf("Number of printf statements: %d\n", print);
    printf("Number of scanf statements: %d\n", scan);
    return 0;
}

int yywrap() {
    return 1;
}