#!/bin/sh
HOST=xavier.h4x0r.space           # TODO: Hostname from Task 04
TEXT=doorman.txt

while [ $# -gt 0 ]; do  # TODO: While there are items left in arguments queue
    PORT=$1           # TODO: Set PORT to first item in arguments queue

    # TODO: When HTTP response contains the word "doorman", print the contents
    # of $TEXT, and then exit the loop
    if curl -s http://$HOST:$PORT | tee $TEXT | grep -q -i doorman; then
        echo "DOORMAN found on port $PORT"
        cat $TEXT
        break
    fi 

    shift            # TODO: Pop the first item in the arguments queue to move to next item
done

