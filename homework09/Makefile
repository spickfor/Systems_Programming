CC=		gcc
CFLAGS=		-g -Wall -std=gnu99 -Iinclude
LD=		gcc
LIBS=           -lcrypto
LDFLAGS=	-Llib
AR=		ar
ARFLAGS=	rcs
TARGETS=	bin/thor

# -----------------------------------------------------------------------------

all:		$(TARGETS)

# TODO: Add rules for lib/libthor.a, bin/unit_{timestamp,socket,request,hammer},
# bin/thor and any objects they require

# -----------------------------------------------------------------------------

test:
	@$(MAKE) -sk test-all

test-all:               test-timestamp test-socket test-request test-hammer test-thor

test-timestamp:		bin/unit_timestamp
	@bin/test_timestamp.sh

test-socket:		bin/unit_socket
	@bin/test_socket.sh

test-request:		bin/unit_request
	@bin/test_request.sh

test-hammer:		bin/unit_hammer
	@bin/test_hammer.sh

test-thor:		bin/thor
	@bin/test_thor.sh

%.o: %.c
		$(CC) $(CFLAGS) -c -o $@ $<

lib/libthor.a: src/hammer.o src/request.o src/socket.o src/timestamp.o
		$(AR) $(ARFLAGS) $@ $^

bin/unit_timestamp: src/thor.o lib/libthor.a
		$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

bin/unit_socket: tests/unit_socket.o lib/libthor.a 
		$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

bin/unit_request: tests/unit_request.o lib/libthor.a 
		$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

bin/unit_hammer: tests/unit_hammer.o lib/libthor.a 
		$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

bin/thor: src/thor.o lib/libthor.a 
		$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) bin/unit_* lib/*.a src/*.o tests/*.o *.log *.input

.PHONY:		all test clean
