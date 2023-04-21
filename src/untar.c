#include "header.h"

int main(int argc, char *argv[]) {

    if(argc != 2) {
        fprintf(stderr, "Usage: %s archive\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Descrittore file archivio
    int fd_arch = open(argv[1], O_RDONLY);
    if(fd_arch == -1) {
        perror("Dest file opening error");
        exit(EXIT_FAILURE);
    }

    header_t *h = malloc(sizeof(header_t));
    if(!h) {
        perror("Malloc error");
        exit(EXIT_FAILURE);
    }

    ssize_t r = read_from_IO(fd_arch, (char *) h, sizeof(header_t));
    char *filename = NULL;

    while(r) {

        // printf("Header: %lu %lu\n", h->len, h->size);
        // fflush(stdout);

        filename = malloc(sizeof(*filename) * h->len);

        if(read_from_IO(fd_arch, filename, h->len) == -1) {
            perror("Reading error");
            exit(EXIT_FAILURE);
        }
        printf("Filename: %s\n", filename);
        fflush(stdout);

        free(filename);
        filename = NULL;

        printf("-- Contenuto --\n");
        fflush(stdout);
        echo_IO(fd_arch, STDOUT, h->size);

        printf("-- --------- --\n\n\n");
        fflush(stdout);

        r = read_from_IO(fd_arch, (char *) h, sizeof(header_t));
    }

    exit(EXIT_SUCCESS);

}