#!/usr/bin/env python3

import sys

results = []
for number in sys.stdin:
    number = number.strip()
    if int(number) % 2 == 0:
        results.append(number)

print(' '.join(results))