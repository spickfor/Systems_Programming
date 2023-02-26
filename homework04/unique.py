#!/usr/bin/env python3

import os
import sys

# Functions

def usage(status=0):
    ''' Display usage message and exit with status. '''
    progname = os.path.basename(sys.argv[0])
    print(f'''Usage: {progname} [flags]

    -c      Prefix lines by the number of occurrences
    -d      Only print duplicate lines
    -i      Ignore differences in case when comparing, prints out full line in lowercase
    -u      Only print unique lines

By default, {progname} prints one of each type of line.''')
    sys.exit(status)

def count_frequencies(stream=sys.stdin, ignore_case=False):
    ''' Count the line frequencies from the data in the specified stream while
    ignoring case if specified. '''
    counts = {}
    for line in stream:
        line = line.strip()
        if ignore_case:
            line = line.lower()
        counts[line] = counts.get(line, 0) +1
    return counts


def print_lines(frequencies, occurrences=False, duplicates=False, unique_only=False):
    ''' Display line information based on specified parameters:

    - occurrences:  if True, then prefix lines with number of occurrences
    - duplicates:   if True, then only print duplicate lines
    - unique_only:  if True, then only print unique lines
    '''
    
    for line, count in frequencies.items():
        if duplicates and count < 2:
            continue
        if unique_only and count > 1:
            continue
        if occurrences:
            print(f'{count:>7} {line}')
        else:
            print(line)



def main():
    ''' Process command line arguments, count frequencies from standard input,
    and then print lines. '''
    arguments = sys.argv[1:]
    ignorecase = False
    prefix = False
    unique = False
    duplicate = False

    while arguments and arguments[0].startswith('-'):
        argument = arguments.pop(0)                     
        if argument == '-i':
            ignorecase = True
        elif argument == '-h':
            usage(0)
        elif argument == '-c':
            prefix = True
        elif argument == '-u':
            unique = True
        elif argument == '-d':
            duplicate = True
        else:
            usage(1)

    stream = sys.stdin
    frequency = count_frequencies(stream,ignorecase)

    print_lines(frequency,prefix,duplicate,unique)




# Main Execution

if __name__ == '__main__':
    main()