CFLAGS=-Wall -Wextra -Wpedantic -g

obj/%.o: src/%.c
	gcc $(CFLAGS) $< -c -o $@

all: obj/tar.o obj/untar.o obj/search.o obj/header.o
	gcc obj/tar.o obj/header.o -o tar
	gcc obj/untar.o obj/header.o -o untar
	gcc obj/search.o obj/header.o -o search

.PHONY:clean
clean:
	$(RM) obj/tar.o obj/untar.o obj/search.o obj/header.o tar untar search
