#include "header.h"

int main(int argc, char *argv[]) {

    if(argc != 3) {
        fprintf(stderr, "Usage: %s archive file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Descrittore file archivio
    int fd_arch = open(argv[1], O_RDONLY);
    if(fd_arch == -1) {
        perror("archive file opening error");
        exit(EXIT_FAILURE);
    }

    header_t *h = malloc(sizeof(header_t));
    if(!h) {
        perror("Malloc error");
        exit(EXIT_FAILURE);
    }

    ssize_t r = read_from_IO(fd_arch, (char *) h, sizeof(header_t));
    if(!r || r == -1) exit(EXIT_FAILURE);
    char *filename = malloc(h->len);
    if(read_from_IO(fd_arch, filename, h->len) == -1) {
        perror("Reading error");
        exit(EXIT_FAILURE);
    }

    fflush(stdout);
    while( strcmp(filename, argv[2]) ) {   // Il file non corrisponde
        free(filename);
        filename = NULL;

        if(lseek(fd_arch, h->size, SEEK_CUR) == -1) {
            perror("Seeking error");
            exit(EXIT_FAILURE);
        }

        r = read_from_IO(fd_arch, (char *) h, sizeof(header_t));
        if(!r || r == -1) exit(EXIT_FAILURE);

        filename = malloc(h->len);
        if(read_from_IO(fd_arch, filename, h->len) == -1) {
            perror("Reading error");
            exit(EXIT_FAILURE);
        }
        fflush(stdout);
    }

    printf("Filename: %s\n", filename);
    fflush(stdout);

    free(filename);
    filename = NULL;

    printf("\n-- Contenuto --\n");
    fflush(stdout);
    echo_IO(fd_arch, STDOUT, h->size);

    exit(EXIT_SUCCESS);

}