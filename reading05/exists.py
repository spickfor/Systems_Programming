#!/usr/bin/env python3

import sys
import os

#Check if there are no arguments
if (sys.argv[0] == None):
    print("Usage: exists.py file0...")
    

# Check each command line argument
for arg in sys.argv[1:]:
    if os.path.exists(arg):
        print("%s exists!" %arg)
    else:
        sys.exit("%s doesn't exist"%arg)