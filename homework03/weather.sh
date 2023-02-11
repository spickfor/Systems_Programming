#!/bin/sh

# Globals
URL="https://forecast.weather.gov/zipcity.php?inputstring="
ZIPCODE=46556
FORECAST=0
CELSIUS=0


# Functions
usage()	{
    cat 1>&2  <<EOF
	Usage: $(basename $0) [zipcode]
	-c    Use Celsius degrees instead of Fahrenheit for temperature
	-f    Display forecast text after the temperature
	If zipcode is not provided, then it defaults to $ZIPCODE.
EOF
	    exit $1
}

weather_information() {
 curl -Ls $URL$ZIPCODE
}

temperature() {
 		if [ $CELSIUS -eq 1 ]; then
			# Extract temperature information from weather source
			weather_information | grep -E "myforecast" | sed -nE 's/^[ \t]*<p class="myforecast-current-sm">([-0-9]*).*/\1/p'
			else
			weather_information | grep -E "myforecast" | sed -nE 's/^[ \t]*<p class="myforecast-current-lrg">([-0-9]*)&deg;F<\/p>/\1/p'
		fi
}

forecast() {
		# Extract forecast information from weather source
		weather_information | grep -Eo 'myforecast-current[^-]+<'| grep -Eo '>[A-Za-z]*' | tr -d '>' | sed -E 's/^\[ \t]*//;s/[ \t]*$//'
}

# Parse Command Line Options

while [ $# -gt 0 ]; do
	case $1 in
		-h) usage 0;;
		-c)	CELSIUS=1;;
		-f)	FORECAST=1;;
		-*) usage 1;;
		 *) ZIPCODE=$1;break;;
	esac
	shift
done

# Display Info

echo "Temperature: $(temperature) degrees"
if [ $FORECAST -eq 1 ]; then
 	echo "Forecast:    $(forecast)"
fi