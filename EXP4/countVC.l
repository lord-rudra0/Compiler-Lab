%{
    #include<stdio.h>
    int vcount=0;
    int ccount=0;
%}


VOWELS [aeiouAEIOU]
CONSONANTS [a-zA-Z]

%%
{VOWELS} {vcount++;}
{CONSONANTS} {ccount++;}
%%


int main()
{
    printf("Enter the sentence \t");
    yylex();

    printf("Total VOWELS are : %d \n",vcount);
    printf("Total CONSONANTS are : %d \n",ccount);
    return 0;
}

int yywrap()
{
    return 1;
}

