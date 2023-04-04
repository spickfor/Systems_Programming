/* grep.c */

 
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char *PROGRAM_NAME = NULL;

/* Functions */
void usage(int status) {
    fprintf(stderr, "Usage: %s PATTERN\n", PROGRAM_NAME);
    exit(status);
}


bool grep_stream(FILE *stream, const char *pattern) {
    char buffer[BUFSIZ];
    bool found = false;


    while (fgets(buffer, BUFSIZ, stream)) {
        if (strstr(buffer, pattern)) {
            fputs(buffer, stdout);
            found = true;
        }
    }

    return found;

}




/* Main Execution */
int main(int argc, char *argv[]) {
    int argind = 1;

    /* Parse command line arguments */
    PROGRAM_NAME = argv[0];
    if (argc == 1 || (argc > 1 && strcmp(argv[1], "-h") == 0)) {
        usage(0);
    }
    const char *pattern = argv[argind++];


    /* Process each line */
    bool found = grep_stream(stdin, pattern);

    return found ? EXIT_SUCCESS : EXIT_FAILURE;

}

