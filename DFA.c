#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    char *s = NULL;
    char buf[4096];

    if (argc > 1) {
        s = argv[1];
    } else {
        /* Prompt the user then read a line from stdin */
        printf("Enter binary string: ");
        fflush(stdout);
        if (!fgets(buf, sizeof(buf), stdin)) {
            fprintf(stderr, "No input\n");
            return 2;
        }
        /* strip newline */
        size_t n = strlen(buf);
        if (n && buf[n-1] == '\n') buf[n-1] = '\0';
        s = buf;
    }

    /* states: 0=q0 (start), 1=q1 (last was '0'), 2=q2 (last two '01') */
    int state = 0;

    for (size_t i = 0; s[i] != '\0'; ++i) {
        char c = s[i];
        if (c != '0' && c != '1') {
            /* ignore whitespace characters inside input */
            if (c == ' ' || c == '\t' || c == '\r') continue;
            fprintf(stderr, "Invalid character '%c' in input. Only '0' and '1' allowed.\n", c);
            return 2;
        }

        switch (state) {
            case 0: /* q0 */
                if (c == '0') state = 1;
                else state = 0;
                break;
            case 1: /* q1 */
                if (c == '0') state = 1;
                else state = 2;
                break;
            case 2: /* q2 */
                if (c == '0') state = 1;
                else state = 0;
                break;
            default:
                state = 0;
        }
    }

    if (state == 2) {
        puts("ACCEPT");
        return 0;
    } else {
        puts("REJECT");
        return 1;
    }
}
