/* hash.c: hash functions */

#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include <openssl/sha.h>

/**
 * Constants
 * http://isthe.com/chongo/tech/comp/fnv/
 */

#define FNV_OFFSET_BASIS    (0xcbf29ce484222325ULL)
#define FNV_PRIME           (0x100000001b3ULL)

/**
 * Compute FNV-1 hash.
 * @param   data            Data to hash.
 * @param   n               Number of bytes in data.
 * @return  Computed hash as 64-bit unsigned integer.
 */
uint64_t    hash_from_data(const void *data, size_t n) {
    uint64_t hash = FNV_OFFSET_BASIS;
    const unsigned char *p = data;
    while (n > 0) {
        hash ^= (uint64_t) *p;
        hash = hash * FNV_PRIME;
        n--;
        p++;
    }
    return hash;
}

/**
 * Compute SHA1 digest.
 * @param   path            Path to file to checksum.
 * @param   hexdigest       Where to store the computed checksum in hexadecimal.
 * @return  Whether or not the computation was successful.
 */
bool        hash_from_file(const char *path, char hexdigest[HEX_DIGEST_LENGTH]) {
    /* Stat file */
    struct stat file_stat;
    /* Open file for reading */
    if (stat(path, &file_stat) < 0) {
        perror("failed to stat file");
        goto failure;
    }

    FILE *fp = fopen(path, "rb");
    if (fp == NULL) {
        perror("Failed to open file");
        goto failure;
    }
    /* Allocate data buffer */
    char *buffer = malloc(file_stat.st_size);
    if (buffer == NULL) {
        perror("Failed to allocate memory");
        fclose(fp);
        goto failure;
    }
    /* Read data into buffer */
    if (fread(buffer, 1, file_stat.st_size, fp) != file_stat.st_size) {
        perror("Failed to read data from file");
        free(buffer);
        fclose(fp);
        goto failure;
    }

    fclose(fp);

    /* Compute raw SHA1 digest */
    unsigned char sha1_digest[SHA_DIGEST_LENGTH];
    SHA1((unsigned char*)buffer, file_stat.st_size, sha1_digest);

    free(buffer);
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf(&hexdigest[i * 2], "%02x", sha1_digest[i]);
    }

    /* Convert raw SHA1 digest to hexadecimal digest */
    hexdigest[SHA_DIGEST_LENGTH * 2] = '\0';

    return true;

failure:
    /* Clean up */
    return false;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */


