/* thor.c */

#include "hammer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Functions */

void usage(const char *progname, int status) {
    fprintf(stderr, "Usage: %s [options] URL\n", progname);
    fprintf(stderr, "    -n HAMMERS How many times to hammer the URL\n");
    exit(status);
}

/* Main Execution */

int main(int argc, char *argv[]) {
    /* TODO: Parse command line arguments */
    int hammer = 1;
    char *prog = argv[0];
    if (argc == 1){
        usage(prog, 1);
        //return EXIT_FAILURE;
    }
    for(int i = 0; i < argc; i++){
      char *arg = argv[i];

      if (arg[0] == '-'){
        if (strcmp(argv[i], "-h") == 0) {
            usage(prog, 0);
        }else if (strcmp(argv[i], "-n") == 0){
            i++;
            hammer = atoi(argv[i]);
        } else{
            usage(prog,1);
        }
      }
    }
    char *url = argv[argc-1];


    /* TODO: Throw Hammers */
    int status = throw(url, hammer, stdout);
    return !status;

}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */


