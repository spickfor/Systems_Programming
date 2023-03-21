#!/usr/bin/env python3

import os

# Run the ls command and split the output into lines
ls_output = os.popen('/bin/ls -ld /etc/*').read().split('\n')

# Extract the group from each line using a list comprehension and the split method
groups = [line.split()[3] for line in ls_output if line]

# Sort the list of groups and remove duplicates
unique_groups = sorted(set(groups))

# Print each group on a separate line
for group in unique_groups:
    print(group)
    