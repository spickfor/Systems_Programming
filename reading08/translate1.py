#!/usr/bin/env python3

import re

with open('/etc/passwd','r') as f:
    data = f.read()
    matches = re.findall(r':1\d*0:',data)
    print(len(matches))
    