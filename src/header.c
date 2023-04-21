#include "header.h"

ssize_t write_to_IO(const int fd, char *buffer, size_t buff_size) {

    ssize_t res = write(fd, buffer, buff_size);
    while(res && res != -1) {
        buffer += res;
        buff_size -= res;
        res = write(fd, buffer, buff_size);
    }

    return res;

}

ssize_t read_from_IO(const int fd, char *buffer, size_t buff_size) {

    ssize_t res = 0, tmp;
    tmp = read(fd, buffer, buff_size);
    while(tmp && tmp != -1) {
        res += tmp;
        buffer += tmp;
        buff_size -= tmp;
        tmp = read(fd, buffer, buff_size);
    }

    return res;

}

#define BUFF_LEN 1024
ssize_t echo_IO(const int fd_source, const int fd_dest, ssize_t buff_len) {

    char buffer[BUFF_LEN];
    ssize_t rem = buff_len>0 ? min(buff_len, BUFF_LEN) : (ssize_t)-1;

    ssize_t r = read(fd_source, buffer, rem != (ssize_t)-1 ? rem : BUFF_LEN);
    ssize_t wr, tmp;
    while(r && r != -1) {
        wr = write(fd_dest, buffer, r);
        if(wr == -1) return -1;
        while(r - wr) {
            tmp = write(fd_dest, &buffer[wr], r);
            if(tmp == -1) return -1;
            else {
                r -= tmp;
                wr += tmp;
            }
        }
        if(rem != (ssize_t)-1) rem -= wr;
        r = read(fd_source, buffer, rem != (ssize_t)-1 ? min(BUFF_LEN, rem) : BUFF_LEN);
    }

    return r == -1 || wr == -1 ? -1 : 0;

}
#undef BUFF_LEN