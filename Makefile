CC      ?= gcc
CFLAGS  += -O3 -std=gnu99
PREFIX  ?= $(HOME)

hail: hail.c
	$(CC) $(CFLAGS) -o $@ $<

install: hail hail.1
	mkdir -p $(PREFIX)/bin
	mkdir -p $(PREFIX)/share/man/man1
	cp hail $(PREFIX)/bin
	cp hail.1 $(PREFIX)/share/man/man1

clean:
	rm -f hail
