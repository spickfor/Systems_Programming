#!/usr/bin/env python3

import collections
import re
import requests

# Globals

URL = 'https://cse.nd.edu/undergraduate/computer-science-curriculum/'

# Initialize a default dictionary with integer values
counts = collections.defaultdict(int)

# TODO: Make a HTTP request to URL
response = requests.get(URL)
response.raise_for_status()

# TODO: Access text from response object
data = response.text

# TODO: Compile regular expression to match CSE courses (ie. CSE XXXXX)
regex = re.compile(r'CSE [234][0-9]{4}')
regex1 = re.compile(r'CSE [2][0-9]{4}')
regex2 = re.compile(r'CSE [3][0-9]{4}')
regex3 = re.compile(r'CSE [4][0-9]{4}')

#print(regex.findall(data))

# TODO: Search through data using compiled regular expression and count up all
# the courses per class year
for course in re.findall(regex, data):
    if regex1.search(course):
        counts['Sophomore'] += 1
    elif regex2.search(course):
        counts['Junior'] += 1
    elif regex3.search(course):
        counts['Senior'] += 1

# TODO: Sort items in counts dictionary by value in reverse order and
# display counts and class year
for year, count in sorted(counts.items(), key=lambda p: p[1],reverse=True):
    print(f'{count:>7} {year}')