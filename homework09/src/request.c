/* request.c: Make HTTP Requests */

#include "request.h"
#include "macros.h"
#include "socket.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/* Constants */
#define HOST_DELIMITER  "://"
#define PATH_DELIMITER  '/'
#define PORT_DELIMITER  ':'

/* Functions */

/**
 * Construct Request structure by parsing URL string into separate host, port,
 * and path components.
 *
 * @param   url         URL string to parse.
 *
 * @return  Request structure.
 **/
Request *   request_create(const char *url) {
    /* TODO: Copy data to local buffer */
    char *buffer = strdup(url);

    if(!buffer){
        fprintf(stderr, "error: %s\n", strerror(errno));
        return NULL;
    }

    /* TODO: Skip scheme to host */
    char *host = strstr(buffer, HOST_DELIMITER);
    if(!host){
        host = buffer;
    } else {
        host += 3;
    }
    /* TODO: Split host:port from path */
    char *path = strchr(host, PATH_DELIMITER);
    if(!path){
        path = "";
    } else {
        *path = 0;
        path++;
    }
    /* TODO: Split host and port */
    char *port = strchr(host, PORT_DELIMITER);
    if(!port){
        port = "80";
    } else {
        *port = 0;
        port++;
    }
    /* TODO: Allocate Request structure */
    Request *rq = (Request*)malloc(sizeof(Request));
    if (rq == NULL){
        free(buffer);
        return NULL;
    }
    /* TODO: Copy components to URL structure */
    rq->host = strdup(host);
    if(!(rq->host)){
        fprintf(stderr, "error: %s\n", strerror(errno));
        return NULL;
    }


    rq->path = strdup(path);
    if(!(rq->path)){
        fprintf(stderr, "error: %s\n", strerror(errno));
        return NULL;
    }

    rq->port = strdup(port);
    if(!(rq->port)){
        fprintf(stderr, "error: %s\n", strerror(errno));
        return NULL;
    }

    free(buffer);
    return rq;
}

/**
 * Deallocate Request structure.
 *
 * @param   request     Request structure to deallocate.
 **/
void        request_delete(Request *request) {
    free(request->port);
    free(request->host);
    free(request->path);
    free(request);
}

/**
 * Make a HTTP request and write the contents of the response to the specified
 * stream.
 *
 * @param   url         Make a HTTP request to this URL.
 * @param   stream      Write the contents of response to this stream.
 *
 * @return  -1 on error, otherwise the number of bytes written.
 **/
    ssize_t      request_stream(Request *request, FILE *stream) {
    /* TODO: Connect to remote host and port */
    FILE *client_stream = socket_dial(request->host, request->port);
    if(!client_stream){
        return -1;
    }
    /* TODO: Send request to server */
    fprintf(client_stream, "GET /%s HTTP/1.0\r\n", request->path);
    fprintf(client_stream, "Host: %s\r\n", request->host);
    fprintf(client_stream, "\r\n");

    /* TODO: Read response status from server */
    char buffer[BUFSIZ];
    char *status;
    ssize_t content_len = 0;

    fgets(buffer, BUFSIZ, client_stream);
    status = strstr(buffer, "200 OK");

    if(status == NULL) {
        return -1;
    }

    /* TODO: Read response headers from server */
    while(fgets(buffer, BUFSIZ, client_stream)){
        if(strcmp(buffer, "\r\n") == 0) {
            break;
        }
        sscanf(buffer, "Content-Length: %ld", &content_len);
    }


    /* TODO: Read response body from server */
    ssize_t bytes_written = 0;
    ssize_t sz = 0;
    while((sz = fread(buffer, 1, BUFSIZ, client_stream)) > 0){
        bytes_written = bytes_written + sz;
        fwrite(buffer, 1, sz, stream);
    }
    /* TODO: Close connection */
    fclose(client_stream);
    /* TODO: Return number of bytes written and check if it matches Content-Length */
    if(bytes_written == content_len || content_len == 0) {
        return bytes_written;
    }
    return -1;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
