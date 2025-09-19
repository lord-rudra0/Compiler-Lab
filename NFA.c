#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Simple NFA representation for epsilon-closure computation
// Input file format (example):
// states: 0 1 2 3
// start: 0
// accept: 3
// alphabet: a b
// trans:
// 0 a 1
// 0 e 2
// 1 b 1
// 2 a 3
// 2 e 0
// (blank line or EOF ends transitions)

#define MAX_STATES 256
#define MAX_TRANS 1024

typedef struct Transition {
    int from;
    char sym[8]; // symbol or "e" for epsilon
    int to;
} Transition;

int n_states = 0;
int states_list[MAX_STATES];
Transition trans[MAX_TRANS];
int trans_count = 0;

int seen[MAX_STATES];
int closure_set[MAX_STATES];

void add_transition(int f, const char *s, int t) {
    if (trans_count >= MAX_TRANS) {
        fprintf(stderr, "too many transitions\n");
        exit(1);
    }
    trans[trans_count].from = f;
    strncpy(trans[trans_count].sym, s, sizeof(trans[trans_count].sym)-1);
    trans[trans_count].sym[sizeof(trans[trans_count].sym)-1] = '\0';
    trans[trans_count].to = t;
    trans_count++;
}

// compute epsilon-closure of state 'start'
void epsilon_closure(int start) {
    // reset seen and closure
    for (int i = 0; i < n_states; ++i) seen[i] = 0;
    for (int i = 0; i < n_states; ++i) closure_set[i] = 0;

    // stack for DFS
    int stack[MAX_STATES];
    int sp = 0;
    stack[sp++] = start;
    seen[start] = 1;

    while (sp > 0) {
        int s = stack[--sp];
        closure_set[s] = 1;
        // explore epsilon transitions from s
        for (int i = 0; i < trans_count; ++i) {
            if (trans[i].from == s && (strcmp(trans[i].sym, "e") == 0 || strcmp(trans[i].sym, "eps") == 0)) {
                int to = trans[i].to;
                if (!seen[to]) {
                    seen[to] = 1;
                    stack[sp++] = to;
                }
            }
        }
    }
}

void print_closure(int start) {
    epsilon_closure(start);
    // Print in format: epsilon-closure of q0 :q0q1q2
    printf("epsilon-closure of q%d :", start);
    for (int idx = 0; idx < n_states; ++idx) {
        int s = states_list[idx];
        if (s >= 0 && s < MAX_STATES && closure_set[s]) {
            printf("q%d", s);
        }
    }
    printf("\n");
}

void usage(const char *prog) {
    fprintf(stderr, "Usage: %s <nfa-file> [state1 state2 ...]\n", prog);
    fprintf(stderr, "If no states are provided, program will ask interactively.\n");
}

int find_state_index(int s) {
    for (int i = 0; i < n_states; ++i) if (states_list[i] == s) return i;
    return -1;
}

int main(int argc, char **argv) {
    if (argc < 2) { usage(argv[0]); return 1; }
    const char *path = argv[1];
    FILE *f = fopen(path, "r");
    if (!f) { perror("fopen"); return 1; }

    char line[512];
    // parse file line by line
    while (fgets(line, sizeof line, f)) {
        // trim
        char *p = line;
        while (isspace((unsigned char)*p)) p++;
        if (*p == '\0' || *p == '#') continue;

        if (strncmp(p, "states:", 7) == 0) {
            p += 7;
            while (*p) {
                while (isspace((unsigned char)*p)) p++;
                if (!*p) break;
                int v = strtol(p, &p, 10);
                states_list[n_states++] = v;
            }
        } else if (strncmp(p, "trans:", 6) == 0) {
            // read transitions until blank or EOF
            while (fgets(line, sizeof line, f)) {
                char *q = line;
                while (isspace((unsigned char)*q)) q++;
                if (*q == '\0') break;
                if (*q == '#') continue;
                int a, b;
                char sym[16];
                if (sscanf(q, "%d %15s %d", &a, sym, &b) == 3) {
                    add_transition(a, sym, b);
                }
            }
        }
    }
    fclose(f);

    if (n_states == 0) {
        fprintf(stderr, "no states found in file\n");
        return 1;
    }

    // If states provided on command line, compute closures for those states
    if (argc > 2) {
        for (int i = 2; i < argc; ++i) {
            int s = atoi(argv[i]);
            if (find_state_index(s) < 0) {
                fprintf(stderr, "state %d not in states list\n", s);
                continue;
            }
            print_closure(s);
        }
        return 0;
    }

    // No states provided: print closure for all states in the states list
    for (int idx = 0; idx < n_states; ++idx) {
        print_closure(states_list[idx]);
    }

    return 0;
}
