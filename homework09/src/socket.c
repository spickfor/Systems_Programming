/* socket.c: TCP Socket Functions */

#include "socket.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

/**
 * Create socket connection to specified host and port.
 *
 * @param   host        Host string to connect to.
 * @param   port        Port string to connect to.
 *
 * @return  Socket file stream of connection if successful, otherwise NULL.
 **/
FILE *socket_dial(const char *host, const char *port) {
    /* TODO: Lookup server address information */
    struct addrinfo *results;
    struct addrinfo  hints = {
        .ai_family   = AF_UNSPEC, /* Return IPv4 and IPv6 choices */
        .ai_socktype = SOCK_STREAM, /* Use TCP */
    };
    int status;
    if ((status = getaddrinfo(host, port, &hints, &results)) != 0) {
    	fprintf(stderr, "getaddrinfo failed: %s\n", gai_strerror(status));
        return NULL;
    }

    /* TODO: For each server entry, allocate socket and try to connect */
    int socket_fd = -1;
    for (struct addrinfo *p = results; p != NULL && socket_fd < 0; p = p->ai_next) {
	/* Allocate socket */
	if ((socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) {
	    fprintf(stderr, "Unable to make socket: %s\n", strerror(errno));
	    continue;
	}

	/* Establish connection to host */
	if (connect(socket_fd, p->ai_addr, p->ai_addrlen) < 0) {
	    close(socket_fd);
	    socket_fd = -1;
	    continue;
	}
    }

    /* TODO: Release allocate address information */
    freeaddrinfo(results);

    if (socket_fd < 0) {
	fprintf(stderr, "Unable to connect to %s:%s: %s\n", host, port, strerror(errno));
    	return NULL;
    }

    /* TODO: Open file stream from socket file descriptor */
    FILE *socket_file = fdopen(socket_fd, "w+");
    if (!socket_file) {
        fprintf(stderr, "Unable to fdopen: %s\n", strerror(errno));
        close(socket_fd);
        return NULL;
    }
    //fclose(socket_file);
    return socket_file;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */



