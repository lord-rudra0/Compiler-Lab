%{
   int vow_count = 0;
   int con_count = 0;
%}
VOWEL [aeiouAEIOU]
CONSONANT [a-zA-Z]
%%
{VOWEL} {vow_count++;}
{CONSONANT} {con_count++;}
%%

int main() {
    printf("Enter a string:");
    yylex();
    printf("Vowels: %d\n", vow_count);
    printf("Consonants: %d\n", con_count);
    return 0;

}

int yywrap() {
    return 1;
}