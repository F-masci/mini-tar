#include "header.h"

int main(int argc, char *argv[]) {

    if(argc < 3) {
        fprintf(stderr, "Usage: %s dest file1 [file2] [file3] ... [fileN]\n", argv[0]);
        fflush(stderr);
        exit(EXIT_FAILURE);
    }

    // Descrittore file di destinazione
    const int fd_dest = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if(fd_dest == -1) {
        perror("Dest file opening error");
        exit(EXIT_FAILURE);
    }

    // Scorro i file
    header_t f_header;
    char *filename, *aux;
    size_t len;
    int fd;
    for(size_t i=2; i < (size_t) argc; i++) {
        filename = argv[i];
        len = strlen(filename)+1; // Include il terminatore

        fd = open(filename, O_RDONLY);
        if(fd != -1) {
            f_header.len = len;
            f_header.size = (ssize_t) lseek(fd, (size_t) 0, SEEK_END);

            if(f_header.size == (ssize_t)-1) {
                perror("File size computing error");
                exit(EXIT_FAILURE);
            }

            aux = (char *) &f_header;
            if(write_to_IO(fd_dest, aux, sizeof(f_header)) == -1) {
                perror("Writing error");
                exit(EXIT_FAILURE);
            };
            if(write_to_IO(fd_dest, filename, len) == -1) {
                perror("Writing error");
                exit(EXIT_FAILURE);
            };
            if(lseek(fd, (size_t) 0, SEEK_SET) == -1 || echo_IO(fd, fd_dest, 0) == -1) {
                perror("Writing error");
                exit(EXIT_FAILURE);
            }

        } else {
            perror("Source file opening error");
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);

}