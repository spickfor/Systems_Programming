#!/bin/sh
# TODO: Run latency measuring command once for each command line argument 
for host in $@; do
    echo "Measuring latency for $host"
    ping -c 1 $host
    echo
done
