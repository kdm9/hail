CC=gcc
CFLAGS=-O3
LDFLAGS=

all: hail hail.1

hail: hail.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

hail.1: hail.md
	test -f `which ronn` && ronn --roff $<

clean:
	rm -f hail
