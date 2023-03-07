#!/usr/bin/env python3

import sys

print(' '.join(
    # TODO: One-line expression with list comprehension
    [number.strip() for number in sys.stdin if not(int(number.strip()) % 2)]
))