#!/usr/bin/env python3

# cat /etc/passwd | cut -d : -f 7 | sort | uniq -c | sort -srn

'''This command will display the count of unique shell paths 
in the /etc/passwd file, sorted in descending order.

cat /etc/passwd:    Displays the content of the /etc/passwd file.
cut -d : -f 7:      Extracts the seventh column (fields are colon-separated), which is the shell path.
sort:               Sorts the shell paths.
uniq -c:            Counts unique shell paths.
sort -srn:          Sorts the output in descending order of the counts (highest to lowest).'''

from collections import Counter

path = '/etc/passwd'
lis = []

with open(path, 'r') as f:
    for line in f:
        line = line.split(':')
        lis.append(line[6])

lis = sorted(lis)

counts = Counter(lis)

# Sort the dictionary by values
sorted_counts = dict(sorted(counts.items(), key=lambda item: item[1], reverse=True))

# Print the results
for element, count in sorted_counts.items():
    print(f"{count:7} {element}", end='')



