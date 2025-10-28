#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define max 100

int i ,closure_count = 0,t_count = 0;
char input[max][3][100],closer[200][200];
char startstate[20];


int inCloser(const char*state)
{
    for(i=0;i<closure_count;i++)
    {
        if(strcmp(closer[i],state)==0)
        {
            return 1;
        }

       
    }
     return 0;
}


int addCloser(const char*state)
{
    if(!inCloser(state)){
        strcpy(closer[closure_count++],state);
    }

    return 0;
}

void findCloser(const char*state)
{
    addCloser(state);

    for (int k = 0; k < t_count; k++)
    {
        if(strcmp(input[k][0],state)==0 && strcmp(input[k][1],"e")==0)
        {
            if(!inCloser(input[k][2]))
            {
                findCloser(input[k][2]);
            }
        }
    }

}

int main()
{
    FILE*fp=fopen("input.txt","r");
    if(fp==NULL)
    {
        printf("Error In input");
    }
    else
    {
        while(fscanf(fp,"%s %s %s",input[t_count][0],input[t_count][1],input[t_count][2])==3)
        {
            t_count++;
        }
    }
    printf("Enter the starting state: \n");
    scanf("%s",startstate);
    closure_count=0;
    findCloser(startstate);
    printf("E-closer of %s is : { ",startstate);
    for(i=0;i<closure_count;i++){
        printf("%s",closer[i]);
    }

    printf("}\n");
    return 0;

}