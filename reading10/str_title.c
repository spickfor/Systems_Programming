/* str_title: convert strings to title-case */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// function takes char pointer and returns char pointer
char *str_title(const char *s) {
    //allocate mem using strdup
    // strdup allocates a new string which is a duplicate of the input string. 
    // Dynaically allocates mem to store a copy and returns pointer to new string
    // still need to free mem when using strdup
    char *t = strdup(s);
    // control error for if mem can't be allocated.  Return NULL if error
    if(t == NULL) {
        return NULL;
    }

    // create pointer to new string
    char *c = t;
    // while haven't reached end of string '\0'
    while (*c) {
        *c = toupper(*c);
        // changed to index properly
        // skips spaces
        while (*c && !isspace(*c)){
            c++;
        }
        while (*c &&  isspace(*c)) {
            c++;
        }
    }

    return t;
}

int main(int argc, char *argv[]) {
    // parse command line arguments, skipping the executable name.  Had to make for < instead of <= to fix it trying to access mem it couldn't
    for (int i = 1; i < argc; i++) {
        // call function
        char *t = str_title(argv[i]);
        // for if mem wasn't allocated right
        if (t == NULL) {
            //printf("error: memory couldn't be allocated\n");
            return 1;
        }
        
        puts(t);

        // free the memory that was allocated
        free(t);
    }

    return 0;
}