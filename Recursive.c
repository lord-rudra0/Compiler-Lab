#include<stdio.h>
#include<string.h>

//E->TE'
//E'->+TE'|ε
//T->FT'
//T'->*FT'|ε
//F->(E)|id


void E();
void EPrime();
void T();
void TPrime();
void F();
char input[100];
int i = 0;
int err = 0;

int main()
{
    printf("Enter an expression: ");
    gets(input);
    E();
    /* accept if parser succeeded (err==0) and consumed the whole input */
    if (err == 0 && input[i] == '\0')
        printf("Accepted\n");
    else
        printf("Rejected\n");
}

void E()
{
    T();
    EPrime();
}
void EPrime()
{
    if (input[i] == '+')
    {
        i++;
        T();
        EPrime();
    }
}

void T()
{
    F();
    TPrime();
}

void TPrime()
{
    if (input[i] == '*')
    {
        i++;
        F();
        TPrime();
    }
}

void F()
{
    if (input[i] == '(')
    {
        i++;
        E();
        if (input[i] == ')')
            i++;
        else
            err = 1;
    }
    else if (input[i] >= 'a' && input[i] <= 'z')
    {
        i++;
    }
    else
        err = 1;
}


