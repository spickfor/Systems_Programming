#!/usr/bin/env python3

import concurrent.futures
import hashlib
import os
import string
import sys

# Constants
ALPHABET = string.ascii_lowercase + string.digits

# Functions
def usage(exit_code=0):
    progname = os.path.basename(sys.argv[0])
    print(f'''Usage: {progname} [-a ALPHABET -c CORES -l LENGTH -p PATH -s HASHES]
    -a ALPHABET Alphabet to use in permutations
    -c CORES    CPU Cores to use
    -l LENGTH   Length of permutations
    -p PREFIX   Prefix for all permutations
    -s HASHES   Path of hashes file''')
    sys.exit(exit_code)


def md5sum(s):
    ''' Compute md5 digest for given string. '''
    return hashlib.md5(s.encode('utf-8')).hexdigest()


def permutations(length, alphabet=ALPHABET):
    ''' Recursively yield all permutations of alphabet up to given length. '''

    # check length
    if length == 0:
        return

# iterate through alphabet create permutaions
    if length == 1:
       for letter in alphabet:
           yield letter
    else:
        for letter in alphabet:
            for permutation in permutations(length-1,alphabet):
                yield letter + permutation


def flatten(sequence):
    ''' Flatten sequence of iterators. '''
    # iterate by row in the input sequence
    for row in sequence:
        for value in row:
            yield value


def crack(hashes, length, alphabet=ALPHABET, prefix=''):
    ''' Return all password permutations of specified length that are in hashes
    by sequentially trying all permutations. '''
 
    return [prefix+permutation for permutation in permutations(length,alphabet) if md5sum(prefix+permutation) in hashes]


def whack(arguments):
   ''' Call the crack function with the specified list of arguments '''
   return crack(*arguments)


def smash(hashes, length, alphabet=ALPHABET, prefix='', cores=1):
    ''' Return all password permutations of specified length that are in hashes
    by concurrently subsets of permutations concurrently.
    '''
    arguments = ((hashes,length-1,alphabet,prefix+letter) for letter in alphabet)

    # allows parallelism so that multiple cores can run and improve speed
    with concurrent.futures.ProcessPoolExecutor(cores) as executor:
        return flatten(executor.map(whack, arguments))


# Main Execution
def main():
    arguments   = sys.argv[1:]
    alphabet    = ALPHABET
    cores       = 1
    hashes_path = 'hashes.txt'
    length      = 1
    prefix      = ''

    # Parse command line arguments and select what to set
    while arguments and arguments[0].startswith('-'):
        flag = arguments.pop(0)
        if flag == '-a':
            alphabet = arguments.pop(0)
        elif flag == '-c':
            cores = int(arguments.pop(0))
        elif flag == '-l':
            length = int(arguments.pop(0))
        elif flag == '-p':
            prefix = arguments.pop(0)
        elif flag == '-s':
            hashes_path = arguments.pop(0)
        elif flag == '-h':
            usage(0)
        else:
            usage(1)

    #Load hashes set
    hashSet = {hashVal.strip() for hashVal in open(hashes_path,"r")}

    #call crack or smash function based on need
    if cores < 2 or length == 1:
        iterable = crack(hashSet, length, alphabet,prefix)
    else:
        iterable = smash(hashSet, length, alphabet, prefix, cores)

    # print passwords
    for password in iterable:
        print(password)

# to control when main is called incase its used as library
if __name__ == '__main__':
    main()