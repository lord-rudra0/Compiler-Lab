%{
    #include<stdio.h>
    int scount=0;
    int pcount=0;
%}


%%
"printf" {printf("writef");pcount++;}
"scanf" {printf("readf");scount++;}

%%

int main()
{
    FILE*fp;
    fp=fopen("expinput.txt","r");

    if(fp==NULL)
    {
        printf("error");
    }

    else{
        yyin=fp;

        yylex();
        printf("Total printf are %d \n ",pcount);
        printf("Total scanf are %d \n ",scount);


    }
}

int yywrap()
{
    return 1;
}