CC=gcc
CFLAGS=-O3 -std=gnu99
PREFIX=~

all: hail hail.1

hail: hail.c
	$(CC) $(CFLAGS) -o $@ $<

hail.1: hail.md
	test -e `which ronn` && ronn --roff $<

install: hail hail.1
	mkdir -p $(PREFIX)/bin
	mkdir -p $(PREFIX)/man/man1
	cp hail $(PREFIX)/bin
	cp hail.1 $(PREFIX)/man/man1

clean:
	rm -f hail

clean-all:
	rm -f hail hail.1
