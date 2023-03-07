#!/usr/bin/env python3

import sys

def evens(stream):
    # TODO: Implementation that uses yield statement
    for number in stream:
        number = number.strip()
        if not int(number) % 2:
            yield number

print(' '.join(evens(sys.stdin)))
