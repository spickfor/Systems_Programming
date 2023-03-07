#!/usr/bin/env python3

import sys

print(' '.join(
    # TODO: One-line expression with map, filter, lambda
    filter(lambda i: not (int(i) % 2), map(str.strip, sys.stdin ))
))


#print(' '.join(filter(lambda x: int(x) % 2 == 0, map(str.strip, sys.stdin))))