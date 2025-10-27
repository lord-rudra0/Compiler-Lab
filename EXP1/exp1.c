#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char *keyword[] = {
    "int", "char", "case", "break", "return",
    "for", "while", "if", "else", NULL
};

char *spChar[] = {
    "(", ")", "{", "}", "[", "]", "<", ">", ";", ",", ".", "#", NULL
};

int isKeyword(const char *word)
{
    for (int j = 0; keyword[j] != NULL; j++) {
        if (strcmp(word, keyword[j]) == 0)
            return 1;
    }
    return 0;
}

int isSpecialChar(char ch)
{
    char temp[2] = {ch, '\0'};
    for (int j = 0; spChar[j] != NULL; j++) {
        if (strcmp(temp, spChar[j]) == 0)
            return 1;
    }
    return 0;
}

int isNumber(const char *word)
{
    for (int i = 0; word[i] != '\0'; i++) {
        if (!isdigit(word[i]))
            return 0;
    }
    return 1;
}

int main()
{
    FILE *fp = fopen("expinput.txt", "r");
    if (!fp) {
        printf("Error: cannot open file.\n");
        return 1;
    }

    char word[100];
    int ch, i = 0;

    while ((ch = fgetc(fp)) != EOF)
    {
        if (isalnum(ch) || ch == '_') {
            word[i++] = ch;
        } 
        
        else
         {
            if (i > 0) 
            {
                word[i] = '\0';
                i = 0;

                if (isKeyword(word))
                    printf("%s : keyword\n", word);
                else if (isNumber(word))
                    printf("%s : number\n", word);
                else
                    printf("%s : identifier\n", word);
            }

            if (isSpecialChar(ch))
                printf("%c : special character\n", ch);
        }
    }

    fclose(fp);
    return 0;
}


// fputs()	Prints the whole line in the file and a newline at the end.
// fputc()	Prints a single character into the file.
// fputw()	Prints a number to the file.
// fscanf()	Use formatted string and variable arguments list to take input from a file.
// fgets()	Input the whole line from the file.
// fgetc()	Reads a single character from the file.
// fgetw()	Reads a number from a file.



// fputs("hah ujhsud\n",fp);
        // fputc('h',fp);
        // printf("file is opened ");
        // // fprintf(fp,"%s",str);

        //  printf("\nReading file using fgets():\n");

        // while(fgets(line,sizeof(line),fp))
        // {
        //     printf("%s",line);
        // }
