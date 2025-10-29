#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int n, m = 0, p, i = 0, j = 0;
char a[10][10], f[10];

void follow(char c);
void first(char c);

int main() {
    int z;
    char c, ch;

    printf("Enter the number of productions: ");
    scanf("%d", &n);
    printf("Enter the productions (like E=TR):\n");

    for (i = 0; i < n; i++) {
        scanf("%s", a[i]);
    }

    do {
        m = 0;
        printf("\nEnter element whose FIRST and FOLLOW is to be found: ");
        scanf(" %c", &c);  // notice space before %c — important!

        first(c);
        printf("FIRST(%c) = { ", c);
        for (i = 0; i < m; i++) {
            printf("%c ", f[i]);
        }
        printf("}\n");

        strcpy(f, "");  // reset first/follow array
        m = 0;

        follow(c);
        printf("FOLLOW(%c) = { ", c);
        for (i = 0; i < m; i++) {
            printf("%c ", f[i]);
        }
        printf("}\n");

        printf("\nContinue? (1=Yes / 0=No): ");
        scanf("%d", &z);
    } while (z == 1);

    return 0;
}

void first(char c) {
    int k;
    if (!isupper(c)) {
        f[m++] = c;
        return;
    }

    for (k = 0; k < n; k++) {
        if (a[k][0] == c) {
            if (a[k][2] == '$')
                f[m++] = '$';
            else if (islower(a[k][2]))
                f[m++] = a[k][2];
            else
                first(a[k][2]);
        }
    }
}

void follow(char c) {
    if (a[0][0] == c)
        f[m++] = '$';

    for (i = 0; i < n; i++) {
        for (j = 2; j < strlen(a[i]); j++) {
            if (a[i][j] == c) {
                if (a[i][j + 1] != '\0') {
                    first(a[i][j + 1]);
                }

                if (a[i][j + 1] == '\0' && c != a[i][0]) {
                    follow(a[i][0]);
                }
            }
        }
    }
}
