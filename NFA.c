#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void epsilon_closure(int n, int T, int *from, int *to, char *sym, const int start_set[], int closure[]) {
    int *stack = malloc(n * sizeof(int));
    int top = 0;
    for (int i = 0; i < n; ++i) {
        closure[i] = start_set[i];
        if (closure[i]) stack[top++] = i;
    }
    while (top > 0) {
        int s = stack[--top];
        for (int i = 0; i < T; ++i) {
            if (from[i] == s && sym[i] == 'e' && !closure[to[i]]) {
                closure[to[i]] = 1;
                stack[top++] = to[i];
            }
        }
    }
    free(stack);
}

void move_by_symbol(int n, int T, int *from, int *to, char *sym, const int cur[], char c, int out[]) {
    for (int i = 0; i < n; ++i) out[i] = 0;
    for (int i = 0; i < T; ++i) {
        if (sym[i] == c && cur[from[i]]) out[to[i]] = 1;
    }
}

int main(void) {
    int n;
    printf("Number of states: ");
    if (scanf("%d", &n) != 1 || n <= 0) { printf("Invalid number of states\n"); return 1; }

    int T;
    printf("Number of transitions: ");
    if (scanf("%d", &T) != 1 || T < 0) { printf("Invalid transitions count\n"); return 1; }

    int *from = malloc(T * sizeof(int));
    int *to = malloc(T * sizeof(int));
    char *sym = malloc(T * sizeof(char));
    for (int i = 0; i < T; ++i) {
        printf("Transition %d (format: from symbol to) [use 'e' for epsilon]: ", i+1);
        // read symbol as string to accept whitespace-safe input
        char s[16];
        if (scanf("%d %15s %d", &from[i], s, &to[i]) != 3) { printf("Bad transition input\n"); return 1; }
        sym[i] = s[0];
        if (from[i] < 0 || from[i] >= n || to[i] < 0 || to[i] >= n) {
            printf("Transition has invalid state index\n"); return 1;
        }
    }

    int start;
    printf("Start state: ");
    if (scanf("%d", &start) != 1 || start < 0 || start >= n) { printf("Invalid start state\n"); return 1; }

    int f;
    printf("Number of final states: ");
    if (scanf("%d", &f) != 1 || f < 0) { printf("Invalid final count\n"); return 1; }
    int *final = calloc(n, sizeof(int));
    for (int i = 0; i < f; ++i) {
        int fs;
        if (scanf("%d", &fs) != 1 || fs < 0 || fs >= n) { printf("Invalid final state\n"); return 1; }
        final[fs] = 1;
    }

    // consume leftover newline before reading the string
    int c = getchar();
    while (c != '\n' && c != EOF) c = getchar();

    char input[1024];
    printf("Input string (use no 'e' in string; epsilon is only for transitions): ");
    if (!fgets(input, sizeof(input), stdin)) return 1;
    // strip newline
    size_t len = strlen(input);
    if (len > 0 && input[len-1] == '\n') input[len-1] = '\0';

    // current set: boolean arrays of size n
    int *cur = calloc(n, sizeof(int));
    int *tmp = calloc(n, sizeof(int));
    int *closure = calloc(n, sizeof(int));

    // start with epsilon-closure of start state
    for (int i = 0; i < n; ++i) cur[i] = 0;
    cur[start] = 1;
    epsilon_closure(n, T, from, to, sym, cur, closure);
    for (int i = 0; i < n; ++i) cur[i] = closure[i];

    // process each character
    for (size_t idx = 0; idx < strlen(input); ++idx) {
        char ch = input[idx];
        // compute move on ch
        move_by_symbol(n, T, from, to, sym, cur, ch, tmp);
        // compute epsilon-closure of tmp -> new cur
        epsilon_closure(n, T, from, to, sym, tmp, closure);
        for (int i = 0; i < n; ++i) cur[i] = closure[i];
    }

    // check acceptance
    int accept = 0;
    for (int i = 0; i < n; ++i) if (cur[i] && final[i]) { accept = 1; break; }

    printf("%s\n", accept ? "Accepted" : "Rejected");

    free(from); free(to); free(sym); free(final);
    free(cur); free(tmp); free(closure);
    return 0;
}