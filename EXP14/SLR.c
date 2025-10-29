#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int i=0,j=0,k=0,z=0,l=0;
char input[100], stk[100], ac[20], act[20];

void check();
void printResult(int isaccepted);

int main()
{
    printf("\nGRAMMAR is:\n");
    printf("E -> E+E\nE -> E*E\nE -> (E)\nE -> id\n");
    
    printf("\nEnter input string: ");
    scanf("%s", input);

    l = strlen(input);
    strcpy(act, "Shift -->");
    printf("\n\nStack\t\tInput\t\tAction");

    for (i = 0, j = 0, k = 0; j < l; j++)
    {
        if (input[j] == 'i' && input[j+1] == 'd')
        {
            stk[k++] = 'i';
            stk[k++] = 'd';
            stk[k] = '\0';
            j++; // Skip next 'd'
            printf("\n$%s\t\t%s$\t%s id", stk, input + j + 1, act);
            check();
        }
        else
        {
            stk[k++] = input[j];
            stk[k] = '\0';
            printf("\n$%s\t\t%s$\t%s", stk, input + j + 1, act);
            check();
        }
    }

    // Final reduction after complete input
    int prev_len;
    do {
        prev_len = strlen(stk);
        check();
    } while (strlen(stk) != prev_len);

    if (strcmp(stk, "E") == 0)
        printResult(1);
    else
        printResult(0);

    return 0;
}

void check()
{
    strcpy(ac, "Reduce to E");

    for (z = 0; z < k; z++)
    {
        // E → id
        if (stk[z] == 'i' && stk[z + 1] == 'd')
        {
            stk[z] = 'E';
            strcpy(stk + z + 1, stk + z + 2);
            k = strlen(stk);
            printf("\n$%s\t\t%s$\t%s (E -> id)", stk, input + j + 1, ac);
            z = -1;
        }

        // E → (E)
        else if (stk[z] == '(' && stk[z + 1] == 'E' && stk[z + 2] == ')')
        {
            stk[z] = 'E';
            strcpy(stk + z + 1, stk + z + 3);
            k = strlen(stk);
            printf("\n$%s\t\t%s$\t%s (E -> (E))", stk, input + j + 1, ac);
            z = -1;
        }

        // E → E*E
        else if (stk[z] == 'E' && stk[z + 1] == '*' && stk[z + 2] == 'E')
        {
            stk[z] = 'E';
            strcpy(stk + z + 1, stk + z + 3);
            k = strlen(stk);
            printf("\n$%s\t\t%s$\t%s (E -> E*E)", stk, input + j + 1, ac);
            z = -1;
        }

        // E → E+E
        else if (stk[z] == 'E' && stk[z + 1] == '+' && stk[z + 2] == 'E')
        {
            stk[z] = 'E';
            strcpy(stk + z + 1, stk + z + 3);
            k = strlen(stk);
            printf("\n$%s\t\t%s$\t%s (E -> E+E)", stk, input + j + 1, ac);
            z = -1;
        }
    }
}

void printResult(int isaccepted)
{
    printf("\n\n-------------------------------------\n");
    if (isaccepted)
        printf("Result: String Accepted ✅\n");
    else
        printf("Result: String Rejected ❌\n");
    printf("-------------------------------------\n");
}
