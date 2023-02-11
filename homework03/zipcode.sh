#!/bin/sh

# Globals
CITY=""
STATE="Indiana"
URL="https://www.zipcodestogo.com/"

# Functions
usage() {
	cat 1>&2 <<MESSAGE
	Usage: zipcode.sh
	-c      CITY    Which city to search
  	-s      STATE   Which state to search (Indiana)
	If no CITY is specified, then all the zip codes for the STATE are displayed.
MESSAGE
	exit $1
}

state_information(){
	curl -sL $URL$STATE

}

# Parse Command Line Options
while [ "$#" -gt 0 ]; do
    case "$1" in
    -h) usage 0;;
	-c) CITY=$2;shift;;
	-s) TEMP=$2;STATE=$(echo "$TEMP"| sed "s/\ /%20/");shift;;
     *) usage 1;;
    esac
    shift
done

if [ -n "$CITY" ]; then
	echo "$(state_information)" | grep -E "\/$CITY\/" | grep -Eo [0-9]{5} | sort -n | uniq
   else
	echo "$(state_information)" | grep -Eo /[0-9]{5}/ | tr -d '/'|sort -n | uniq 
fi

