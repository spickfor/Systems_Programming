/* main.c: string library utility */

#include "str.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char *PROGRAM_NAME = NULL;

/* Flags */

enum {
    /* TODO*: Enumerate Flags */
    STRIP   = 1<<1,
    LOWER   = 1<<2,
    UPPER   = 1<<3,
    TITLE   = 1<<4,
    REVERSE = 1<<5,
    DELETE  = 1<<6
};

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s SOURCE TARGET\n\n", PROGRAM_NAME);
    fprintf(stderr, "Post Translation filters:\n\n");
    fprintf(stderr, "   -s      Strip whitespace\n");
    fprintf(stderr, "   -r      Reverse line\n");
    fprintf(stderr, "   -l      Convert to lowercase\n");
    fprintf(stderr, "   -u      Convert to uppercase\n");
    fprintf(stderr, "   -t      Convert to titlecase\n");
    fprintf(stderr, "   -d      Delete letters in SOURCE\n");
    exit(status);
}

void translate_stream(FILE *stream, char *source, char *target, int flag) {
    /* TODO: Process each line in stream by performing transformations */
    char buffer[BUFSIZ];
    while (fgets(buffer, sizeof(buffer), stream)) {
        str_chomp(buffer);
        if (source != NULL && target != NULL) { str_translate(buffer, source, target); }
        if (flag & DELETE)  { str_delete(buffer, source); }
        if (flag & STRIP)   { str_strip(buffer); }
        if (flag & REVERSE) { str_reverse(buffer); }
        if (flag & LOWER)   { str_lower(buffer); }
        if (flag & UPPER)   { str_upper(buffer); }
        if (flag & TITLE)   { str_title(buffer); }
        
        printf("%s\n", buffer);
    }
}

/* Main Execution */

int main(int argc, char *argv[]) {
    /* TODO: Parse command line arguments */
    PROGRAM_NAME = argv[0];
    int flag     = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            for (int j = 1; argv[i][j] != '\0'; j++) {
                switch (argv[i][j]) {
                    case 'h':
                        usage(0);
                    case 's':
                        flag |= STRIP;
                        break;
                    case 'r':
                        flag |= REVERSE;
                        break;
                    case 'l':
                        flag |= LOWER;
                        break;
                    case 'u':
                        flag |= UPPER;
                        break;
                    case 't':
                        flag |= TITLE;
                        break;
                    case 'd':
                        flag |= DELETE;
                        break;
                    default:
                        usage(1);
                }
            }
        } else {
            break;
        }
    }

    char *source = NULL;
    char *target = NULL;
    
    for (int i = 1; i < argc; i++) {
        if (argv[i] && argv[i][0] != '-') { 
            source = argv[i];
            if (argv[i+1]) {
                target = argv[i+1];
            }
            break;
        }
    }

    

    translate_stream(stdin, source, target, flag);


    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
