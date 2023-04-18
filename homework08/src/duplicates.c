/* duplicates.c */

#include "hash.h"
#include "macros.h"
#include "table.h"

#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>

// S_IFDIR wasn't working, here is a suggested fix:
#ifndef S_IFDIR
#define S_IFDIR 0040000
#endif

/* Globals */

char * PROGRAM_NAME = NULL;

/* Structures */

typedef struct {
    bool count;
    bool quiet;
} Options;

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s paths...\n", PROGRAM_NAME);
    fprintf(stderr, "    -c     Only display total number of duplicates\n");
    fprintf(stderr, "    -q     Do not write anything (exit with 0 if duplicate found)\n");
    exit(status);
}

/**
 * Check if path is a directory.
 * @param       path        Path to check.
 * @return      true if Path is a directory, otherwise false.
 */
bool is_directory(const char *path) {
    struct stat s;
    if(!stat(path, &s)){
        if(s.st_mode & S_IFDIR){
            return true;
        }
    }
    return false;
}

/**
 * Check if file is in table of checksums.
 *
 *  If quiet is true, then exit if file is in checksums table.
 *
 *  If count is false, then print duplicate association if file is in
 *  checksums table.
 *
 * @param       path        Path to file to check.
 * @param       checksums   Table of checksums.
 * @param       options     Options.
 * @return      0 if Path is not in checksums, otherwise 1.
 */
size_t check_file(const char *path, Table *checksums, Options *options) {
    char *hex=calloc(1, HEX_DIGEST_LENGTH);
    hash_from_file(path, hex);

    Value *v=table_search(checksums, hex);
    if(v!=NULL){
        if(options->quiet){
            table_delete(checksums);
            free(options);
            free(hex);
            exit(0);
        }else if(!options->count){
            printf("%s is a duplicate of %s\n", path, v->string);
        }
        free(hex);
        return 1;
    }else{
        Value val={0};
        val.string=strdup(path);
        table_insert(checksums, hex, val, STRING);
        free(val.string);
    }
    free(hex);
    return 0;
}

/**
 * Check all entries in directory (recursively).
 * @param       root        Path to directory to check.
 * @param       checksums   Table of checksums.
 * @param       options     Options.
 * @return      Number of duplicate entries in directory.
 */
size_t check_directory(const char *root, Table *checksums, Options *options) {
    size_t count=0;
    DIR *d=opendir(root);
    if(!d){
        return 0;
    }
    
    for(struct dirent *dir=readdir(d); dir; dir=readdir(d)){
        if(streq(dir->d_name, ".") || streq(dir->d_name, "..")){
            continue;
        }
        char path[BUFSIZ];
        path[0]='\0';
        strcat(path, root);
        strcat(path, "/");
        strcat(path, dir->d_name);

        if(!is_directory(path)){
            count+=check_file(path, checksums, options);
        }else{
            count+=check_directory(path, checksums, options);
        }
    }
    closedir(d);
    return count;
}

/* Main Execution */

int main(int argc, char *argv[]) {
    /* Parse command line arguments */
    size_t t=0;
    int count=1;
    Options o={false, false};
    PROGRAM_NAME=argv[0];

    /*Check each argument*/
    while(count<argc && strlen(argv[count])>1 && argv[count][0]=='-'){
        char*arg=argv[count++];
        switch(arg[1]){
            case 'h':
                usage(0);
                break;
            case 'c':
                o.count=true;
                break;
            case 'q':
                o.quiet=true;
                break;
            default:
                usage(1);
                break;
        }
    }

    Table *checksums=table_create(0);

    while(count<argc && strlen(argv[count])>1){
        char *arg=argv[count++];
        if(is_directory(arg))
            t+=check_directory(arg, checksums, &o);
        else
            t+=check_file(arg, checksums, &o);
    }

    table_delete(checksums);

    /* Display count if necessary */
    if(o.count){
        printf("%ld\n", t);
        return 0;
    }

    if(o.quiet){
        return !(t>0);
    }

    return 0;
    return EXIT_FAILURE;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
