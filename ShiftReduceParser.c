#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char *s;
int pos;
int TRACE = 1;
// For trace-mode: maintain a simple symbol stack for display purposes
#define TRACE_STACK_SIZE 256
char trace_stack[TRACE_STACK_SIZE][32];
int trace_top = -1;
int trace_header_printed = 0;

void print_table_header() {
    if (!TRACE || trace_header_printed) return;
    trace_header_printed = 1;
    // green color
    const char *G = "\033[32m";
    const char *R = "\033[0m";
    printf("%s+--------------------------------+--------------------------------+--------------------------------+%s\n", G, R);
    printf("%s| %-30s | %-30s | %-30s |%s\n", G, "Stack", "Input Buffer", "Parsing Action", R);
    printf("%s+--------------------------------+--------------------------------+--------------------------------+%s\n", G, R);
}

void trace_push(const char *sym) {
    if (trace_top < TRACE_STACK_SIZE-1) {
        trace_top++;
        strncpy(trace_stack[trace_top], sym, 31);
        trace_stack[trace_top][31] = '\0';
    }
}

void trace_pop() {
    if (trace_top >= 0) trace_top--;
}

void print_trace(const char *action) {
    if (!TRACE) return;
    print_table_header();
    // build stack string (concatenate without spaces)
    char stackbuf[128] = {0};
    int idx = 0;
    if (trace_top >= 0) {
        for (int i = 0; i <= trace_top && idx < (int)sizeof(stackbuf)-1; ++i) {
            int n = snprintf(stackbuf+idx, sizeof(stackbuf)-idx, "%s", trace_stack[i]);
            if (n < 0) break;
            idx += n;
        }
    } else {
        strncpy(stackbuf, "$", sizeof(stackbuf)-1);
    }
    // remaining input (truncate)
    char inbuf[128] = {0};
    int inlen = snprintf(inbuf, sizeof(inbuf), "%s", s+pos);
    if (inlen < 0) inbuf[0] = '\0';
    // action (truncate)
    char actbuf[128] = {0};
    snprintf(actbuf, sizeof(actbuf), "%s", action);
    // print with green borders
    const char *G = "\033[32m";
    const char *R = "\033[0m";
    printf("%s| %-30.30s | %-30.30s | %-30.30s |%s\n", G, stackbuf, inbuf, actbuf, R);
}

void skip_spaces() {
    while (s[pos] && isspace((unsigned char)s[pos])) pos++;
}

int accept_id() {
    /* accept identifiers matching [A-Za-z_][A-Za-z0-9_]* */
    skip_spaces();
    if (!s[pos]) return 0;
    if (isalpha((unsigned char)s[pos]) || s[pos] == '_') {
        int start = pos;
        pos++;
        while (s[pos] && (isalnum((unsigned char)s[pos]) || s[pos] == '_')) pos++;
        /* use table trace for accepted id display; no separate printf here */
        return 1;
    }
    return 0;
}

int parseE();
int parseEPrime();
int parseT();
int parseTPrime();
int parseF();

int parseE() {
    trace_push("E"); print_trace("push E");
    if (!parseT()) return 0;
    if (!parseEPrime()) return 0;
    
    print_trace("pop E"); trace_pop();
    return 1;
}

int parseEPrime() {
    trace_push("E'"); print_trace("push E'");
    skip_spaces();
    if (s[pos] == '+') {
        print_trace("match '+'");
        pos++;
        if (!parseT()) return 0;
        if (!parseEPrime()) return 0;
    }
    print_trace("pop E'"); trace_pop();
    /* epsilon is allowed */
    return 1;
}

int parseT() {
    trace_push("T"); print_trace("push T");
    if (!parseF()) return 0;
    if (!parseTPrime()) return 0;
    print_trace("pop T"); trace_pop();
    return 1;
}

int parseTPrime() {
    trace_push("T'"); print_trace("push T'");
    skip_spaces();
    if (s[pos] == '*') {
        print_trace("match '*'");
        pos++;
        if (!parseF()) return 0;
        if (!parseTPrime()) return 0;
    }
    print_trace("pop T'"); trace_pop();
    /* epsilon */
    return 1;
}

int parseF() {
    trace_push("F"); print_trace("push F");
    skip_spaces();
    if (s[pos] == '(') {
        print_trace("match '('");
        pos++;
        if (!parseE()) return 0;
        skip_spaces();
        if (s[pos] == ')') {
            print_trace("match ')'");
            pos++;
            print_trace("pop F"); trace_pop();
            return 1;
        }
        print_trace("pop F"); trace_pop();
        return 0; /* missing closing ) */
    }
    if (accept_id()) {
        print_trace("pop F"); trace_pop();
        return 1;
    }
    print_trace("pop F"); trace_pop();
    return 0;
}

int main(int argc, char **argv) {
    char input[512];
    if (argc > 1 && strcmp(argv[1], "-t") == 0) {
        TRACE = 1;
    }
    printf("Enter input string (identifiers match [A-Za-z_][A-Za-z0-9_]*): ");
    if (!fgets(input, sizeof(input), stdin)) {
        fprintf(stderr, "No input\n");
        return 2;
    }
    input[strcspn(input, "\n")] = '\0';
    s = input; pos = 0;

    int ok = parseE();
    skip_spaces();
    if (ok && s[pos] == '\0') {
        printf("Accepted\n");
        return 0;
    } else {
        printf("Rejected\n");
        return 1;
    }
}

