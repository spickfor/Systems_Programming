CC=             gcc
CFLAGS=         -g -Wall -std=gnu99 -Iinclude
LD=             gcc
LDFLAGS=        -Llib -lssl
LIBS=           -lcrypto
AR=             ar
ARFLAGS=        rcs
TARGETS=        bin/duplicates bin/unit_hash bin/unit_pair bin/unit_table

all:            $(TARGETS)

# TODO: Add rules for bin/unit_hash, bin/unit_pair, bin/unit_table, bin/duplicates

lib/libtable.a: src/hash.o src/pair.o src/table.o
		$(AR) $(ARFLAGS) $@ $^

%.o: %.c
		$(CC) $(CFLAGS) -c -o $@ $<

bin/duplicates: src/duplicates.o lib/libtable.a
		$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

bin/unit_hash: tests/unit_hash.o lib/libtable.a
		$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

bin/unit_pair: tests/unit_pair.o lib/libtable.a
		$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

bin/unit_table: tests/unit_table.o lib/libtable.a
		$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

test:
				@$(MAKE) -sk test-all

test-all:               test-hash test-pair test-table test-duplicates

test-pair:              bin/unit_pair
				@bin/test_pair.sh

test-hash:              bin/unit_hash
				@bin/test_hash.sh

test-table:             bin/unit_table
				@bin/test_table.sh

test-duplicates:        bin/test_duplicates.sh bin/duplicates
				@bin/test_duplicates.sh

clean:
				@echo Cleaning...
				@rm -f $(TARGETS) bin/unit_pair bin/unit_hash bin/unit_table lib/*.a src/*.o tests/*.o *.log *.input

.PHONY:         all test clean
