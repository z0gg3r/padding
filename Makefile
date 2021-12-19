CC=gcc
CFLAGS=-Wall -Wextra -std=c99
LIBS=
PREFIX=/usr/local/bin

OBJQ = padding.c

%.o: src/%.c
	@echo CC $^
	@$(CC) -c -o $@ $< $(CFLAGS)

pad: $(OBJQ)
	@echo CC $^
	@$(CC) -o $@ $^ $(CLFAGS) $(LIBS)
	@rm -f *.o

clean:
	@echo Cleaning dir...
	@rm -f pad *.o

install:
	@echo INSTALL pad
	@cp pad $(PREFIX)
