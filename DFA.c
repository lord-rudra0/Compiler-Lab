#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int find_symbol_index(char *alphabet, int m, char c) {
    for (int i = 0; i < m; ++i)
        if (alphabet[i] == c) return i;
    return -1;
}

int main(void) {
    int n_states, m_alpha;
    printf("Number of states: ");
    if (scanf("%d", &n_states) != 1 || n_states <= 0) return 1;
    printf("Alphabet size: ");
    if (scanf("%d", &m_alpha) != 1 || m_alpha <= 0) return 1;

    char *alphabet = malloc(m_alpha);
    printf("Enter %d symbol(s) (single characters) separated by spaces: ", m_alpha);
    for (int i = 0; i < m_alpha; ++i) {
        scanf(" %c", &alphabet[i]);
    }

    int start;
    printf("Start state (0 to %d): ", n_states - 1);
    scanf("%d", &start);
    if (start < 0 || start >= n_states) {
        fprintf(stderr, "Invalid start state\n");
        return 1;
    }

    int k_accept;
    printf("Number of accepting states: ");
    scanf("%d", &k_accept);
    bool *accepting = calloc(n_states, sizeof(bool));
    printf("Enter %d accepting state index(es) separated by spaces: ", k_accept);
    for (int i = 0; i < k_accept; ++i) {
        int s; scanf("%d", &s);
        if (s >= 0 && s < n_states) accepting[s] = true;
    }

    // allocate transition table and read transitions
    int **trans = malloc(n_states * sizeof(int*));
    for (int i = 0; i < n_states; ++i) {
        trans[i] = malloc(m_alpha * sizeof(int));
        for (int j = 0; j < m_alpha; ++j) trans[i][j] = -1;
    }

    printf("Enter transitions. For each state and symbol give target state index (or -1 for no transition).\n");
    for (int i = 0; i < n_states; ++i) {
        for (int j = 0; j < m_alpha; ++j) {
            printf("delta(%d, '%c') = ", i, alphabet[j]);
            scanf("%d", &trans[i][j]);
            if (trans[i][j] < -1 || trans[i][j] >= n_states) {
                fprintf(stderr, "Invalid target. Use -1 or 0..%d\n", n_states - 1);
                return 1;
            }
        }
    }

    // flush remainder of line and switch to fgets for test strings
    int c; while ((c = getchar()) != '\n' && c != EOF) {}

    printf("\nDFA ready. Enter test strings (symbols from the given alphabet). Empty line to quit.\n");
    char buf[1024];
    while (true) {
        printf("Input> ");
        if (!fgets(buf, sizeof(buf), stdin)) break;
        // strip newline
        size_t len = strlen(buf);
        if (len > 0 && buf[len-1] == '\n') buf[len-1] = '\0';
        if (buf[0] == '\0') break;

        int cur = start;
        bool rejected = false;
        for (size_t i = 0; buf[i] != '\0'; ++i) {
            char ch = buf[i];
            int idx = find_symbol_index(alphabet, m_alpha, ch);
            if (idx == -1) { rejected = true; break; }
            int nxt = trans[cur][idx];
            if (nxt == -1) { rejected = true; break; }
            cur = nxt;
        }

        if (!rejected && accepting[cur]) printf("Accepted\n");
        else printf("Rejected\n");
    }

    // free
    for (int i = 0; i < n_states; ++i) free(trans[i]);
    free(trans);
    free(alphabet);
    free(accepting);
    return 0;
}