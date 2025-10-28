#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


char input[100];
int i;
int error=0;
void E();
void EPRIME();
void T();
void TPRIME();
void F();

int main()
{
    printf("Enter the string : ");
    scanf("%s",input);

    E();
    if(strlen(input)==i && error==0)
    {
        printf("\n String Accepted");
    }

    else {
        printf("\n String Rejected");
    }

return 0;


}


void E()
{
    T();
    EPRIME();
}

void EPRIME()
{
    if(input[i]=='+')
    {
        i++;
        T();
        EPRIME();
    }
}

void T()
{
    F();
    TPRIME();
}

void TPRIME()
{
    if(input[i]=='*')
    {
        i++;
        F();
        TPRIME();
    }
}

void F()
{
    if(isalpha(input[i]))
    {
        i++;
    }

    else if(input[i]=='(')
    {
        i++;
        E();
        if(input[i]==')')
        {
            i++;
        }
    }

    else{
        error=1;
    }


}



