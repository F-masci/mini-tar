#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define min(a, b) ((a) > (b) ? (b) : (a))

typedef struct _header_t {

    ssize_t size; // Dimensione in Byte del file
    ssize_t len; // Lunghezza del nome del file

} header_t;

ssize_t write_to_IO(const int, char *, size_t);
ssize_t read_from_IO(const int, char *, size_t);
ssize_t echo_IO(const int, const int, ssize_t);