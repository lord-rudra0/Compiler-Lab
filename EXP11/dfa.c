#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define max 100
char str[max],f='a';

int main()
{
    printf("Enter the string : ");
    scanf("%s",str);

    for(int i=0;str[i]!='\0';i++)
    {
        switch(f)
        {
            case 'a':
            {
                if (str[i]=='0')
                {
                    f='b';
                }
                else{
                    f='a';
                }
                break;
            }

            case 'b':
            {
                if (str[i]=='0')
                {
                    f='b';
                }
                else{
                    f='c';
                }

                break;
            }


            case 'c':
            {
                if (str[i]=='0')
                {
                    f='a';
                }
                else{
                    f='b';
                }

                break;
            }

            default:
                printf("Invalid Exp");
                break;
        }
    }

    if (f=='c')
    {
        printf("String %s Accepted ",str);
    }

    else{
        printf("String %s Rejected ",str);
    }
}