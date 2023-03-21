#!/usr/bin/env python3

import requests
import re

response = requests.get('http://yld.me/raw/fDIO')
data = response.text.split('\n')
fourth_column = [row.split(',')[3] for row in data if len(row.split(',')) > 3]
matches = [match.group(0) for match in (re.match(r'^M.*', item) for item in fourth_column) if match]
for item in sorted(matches):
    print(item)
    