#!/bin/bash

q1_answer() {
    # TODO: List only the last four first names in sorted order
    curl -sL https://yld.me/raw/g4gJ | cut -d , -f 2 | sort | tail -n 4
}

q2_answer() {
    # TODO: Count how many netids do not have any digits
   curl -sL https://yld.me/raw/g4gJ | cut -d , -f 1 | grep ^[a-zA-Z]*$ | wc -l
}

q3_answer() {
    # TODO: List the last names that contain two consecutive vowels in sorted order
    curl -sL https://yld.me/raw/g4gJ | cut -d , -f 3 | grep -E '.*[aeiou]{2}.*' | sort
}

q4_answer() {
    # TODO: List all the phone numbers that contain two of the same even number
    # and ends with that number in sorted order
    curl -sL https://yld.me/raw/g4gJ | cut -d , -f 4 | grep -E '.*([2468]).*\1$' | sort
}

q5_answer() {
    # TODO: List all the last names that fully appear in the corresponding
    # netids in sorted order
    curl -sL https://yld.me/raw/g4gJ | cut -d ',' -f 1,3 | sed 's/[0-9]//g' | sed 's/^.//' | tr A-Z a-z | awk -F ',' '{ if ($1 == $2) print $2 }' | sort | sed 's/^./\u&/'
}

q6_answer() {
    # TODO: List in sorted order all the netids of people whose phone number
    # contains at least one duplicate digit in the last four numbers
    curl -sL https://yld.me/raw/g4gJ | cut -d ',' -f 1,4 | grep -E ',.*-.*-.*([0-9]).*\1' | cut -d ',' -f 1 | sort
}
