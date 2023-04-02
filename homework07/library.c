/* library.c: string utilities library */

#include "str.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

/**
 * Convert all characters in string to lowercase.
 * @param   s       String to convert
 **/
void	str_lower(char *s) {
    while (*s != '\0') {
        //convert to lower
        *s = tolower(*s);
        //move to next char in string
        s++;
    }
}

/**
 * Convert all characters in string to uppercase.
 * @param   s       String to convert
 **/
void	str_upper(char *s) {
    while (*s != '\0') {
        //convert to lower
        *s = toupper(*s);
        //move to next char in string
        s++;
    }
}

/**
 * Convert all characters in string to titlecase.
 * @param   s       String to convert
 **/
void	str_title(char *s) {
    //initilaize bool for start of word or not
    int start = 1;      //assumes the need to capitalize first word
    
    while(*s != '\0') {
        // test if its a letter
        if (isalpha(*s)) {
            //if start of word then capitalize
            if (start) {
                *s = toupper(*s);
                start = 0;
            }
            // else make lowercase
            else {
                *s = tolower(*s);
            }
        // assume if its not a letter its a word boundary (space) and reset word starting variable
        }  
        else {
            start = 1;
        }
        s++;
    }
}


/**
 * Removes trailing newline (if present).
 * @param   s       String to modify
 **/
void    str_chomp(char *s) {
    if (s == NULL || strlen(s) == 0) {
        return;
    }
    char *end = s + strlen(s) -1;
    if (*end == '\n') {
        *end = '\0';
    }
}

/**
 * Removes whitespace from front and back of string (if present).
 * @param   s       String to modify
 **/
void    str_strip(char *s) {
    // initilize pointers to head and tail
    char *head = s;
    char *tail = s + strlen(s)-1;
    //moe head pointer foward until it is pointing to a non-whitespace
    while (isspace(*head)) {
        head++;
    }
    //move tail backward until points to non-whitespace
    while(isspace(*tail)) {
        tail--;
    }
    //copy chars from head to tail to front of string
    while (head <= tail) {
        *s = *head;
        s++;
        head++;
    }
    //null to terminate resultant string
    *s = '\0';
}

/**
 * Reverses a string.
 * @param   s       String to reverse
 **/
void    str_reverse(char *s) {
    //return if null
    if (s== NULL) {
        return;
    }
    //initialize pointers
    char *start = s;
    char *end = s + strlen(s) - 1;
    //iterate through
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

/**
 * Deletes characters from a string.
 * @param   s       String to reverse
 * @param   from    String with letters to remove
 **/
void str_delete(char *s, char *from) {
    //initialize the lookup table to 0's
    int lookup[256] = {0};
    // mark characters in lookup table
    for (char *c = from; *c; c++) {
        lookup[(int)*c] = 1;
    }
    // rewrite string with characters not marked in lookup table
    char *i, *j;
    for (i = s, j = s; *i; i++) {
        // if false(0)
        if (!lookup[(int)*i]) {
            *j = *i;
            j++;
        }
    }
    *j = '\0';  // null terminate the resultant string
}


/**
 * Replaces all instances of 'from' in 's' with corresponding values in 'to'.
 * @param   s       String to translate
 * @param   from    String with letters to replace
 * @param   to      String with corresponding replacment values
 **/

void str_translate(char *s, char *from, char *to) {
    // initialize lookup table to all 0's
    int lookup[256] = {0};
    // populate lookup with mapping
    char *pfrom = from;
    char *pto = to;
    while (*pfrom) {
        lookup[(unsigned char)*pfrom] = *pto;
        pfrom++;
        pto++;
    }
    // translate s using lookup table
    char *ps = s;
    while (*ps) {
        if (lookup[(unsigned char)*ps] != 0) {
            *ps = lookup[(unsigned char)*ps];
        }
        ps++;
    }
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
