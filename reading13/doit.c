/* doit.c */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/wait.h>
#include <unistd.h>

/**
 * Run specified program with the bourne shell.
 * @param     command     Command to run.
 * @return    Exit status of child process.
 */
int doit(const char *command) {
    int status = 0;
    
    // TODO: fork child process
    int rc = fork();
    // TODO: Check three cases
    //  1. Error:  print error message based on errno
    //      Return EXIT_FAILURE
    if (rc < 0) {
        fprintf(stderr, "Error: fork failed %s\n",strerror(errno));
        return EXIT_FAILURE;
    }
    //
    //  2. Child:  execute command using execl (Hint: `man system`)
    //      Be sure to exit with EXIT_FAILURE if execl fails
    else if( rc == 0) {
        int check = execl("/bin/sh","sh", "-c", command, NULL);
        if (check == -1) {
            fprintf(stderr, "Error: execl failed %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    //
    //  3. Parent: wait until child returns
    //      Return with status of child process
    else{
        waitpid(rc,&status,0);
    }
    return status;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
	fprintf(stderr, "Usage: %s COMMAND\n", argv[0]);
	return EXIT_SUCCESS;
    }

    return WEXITSTATUS(doit(argv[1]));
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
