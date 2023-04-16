CC=             gcc
CFLAGS=         -g -Wall -Werror -std=gnu99
TARGETS=        ncat

all:            $(TARGETS)

# TODO: Add rule for ncat

test:
	        @$(MAKE) -sk test-all

test-all:	test-ncat

test-ncat:	ncat
	curl -sLO https://raw.githubusercontent.com/nd-cse-20289-sp23/cse-20289-sp23-assignments/master/reading12/test_ncat.sh
	chmod +x test_ncat.sh
	./test_ncat.sh

ncat:		ncat.c
	$(CC) $(CFLAGS) -o ncat ncat.c


clean:
	rm -f $(TARGETS)

.SUFFIXES:
