/* hash.h */

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <openssl/sha.h>

/* Constants */

#define HEX_DIGEST_LENGTH   ((SHA_DIGEST_LENGTH<<1) + 1)

/* Functions */

uint64_t    hash_from_data(const void *data, size_t n);
bool        hash_from_file(const char *path, char hexdigest[HEX_DIGEST_LENGTH]);

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
