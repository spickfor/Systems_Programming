/* hammer.c: Make HTTP request and measure bandwidth */

#include "hammer.h"
#include "macros.h"
#include "request.h"
#include "timestamp.h"

#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* Constants */

#define MEGABYTE    (double)(1<<20)

/* Functions */

/**
 * Perform a hammer through by making a HTTP request to the specified URL and
 * printing the contents of the response to the given stream.
 * Function prints the bandwidth of the HTTP transaction if it is successful to
 * stderr.
 *
 * @param   url         Make HTTP request to this URL.
 * @param   stream      Write the contents of each response to this stream.
 *
 * @return  Whether or not the HTTP request was successful.
 **/
bool    hammer(const char *url, FILE *stream) {
    /* TODO: Perform HTTP request */
    Request *rq = request_create(url);
    double start_t = timestamp();
    ssize_t bytes_w = request_stream(rq, stream);

    double end_t = timestamp();
    if(end_t < 0) {
        return false;
    }
    /* TODO: Compute and display bandwidth to stderr if HTTP request was
     * successful */
    if(bytes_w == -1){
        request_delete(rq);
        return false;
    } else {
        double bandwidth = bytes_w / 1048576.0 / (end_t - start_t);
        fprintf(stderr, "Bandwidth: %.2lf MB/s\n", bandwidth);
        request_delete(rq);
        return true;
    }

}

/**
 * Make hammers HTTP requests to the specified url, while writing the contents
 * of the request to the specified stream.
 *
 * Each HTTP request must be performed by a separate child process.
 *
 * Function prints the total elapsed time for all throws to stderr at the end.
 *
 * @param   url         Make HTTP requests to this URL.
 * @param   hammers     The number of HTTP requests to make.
 * @param   stream      Write the contents of each response to this stream.
 *
 * @return  Whether or not all hammer throws were successful.
 **/
bool    throw(const char *url, size_t hammers, FILE *stream) {
    /* TODO: Throw all hammers by spawning child processes that call hammer and
     * exit success if the hammer throw was successful. */
    double start_t = timestamp();
    int stat = 0;

    /* TODO: Collect results of throws by waiting for all children */
    for(size_t i = 0; i < hammers; i++){
        pid_t p = fork();

        if(p == 0){
            exit(hammer(url, stream));
        } else if(p < 0) {
            exit(-1);
        }
    }

    for(size_t i = 0; i < hammers; i++){
        int child_stat;

        while(wait(&child_stat) > 0){
            stat += child_stat;
        }
    }
    double end_t = timestamp();
    /* TODO: Print elapsed time to stderr */
    fprintf(stderr, "Elapsed Time: %.2lf seconds\n", end_t - start_t);
    return stat;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */


