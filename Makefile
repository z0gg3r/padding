CC=gcc
CFLAGS=-Wall -Wextra -std=c99
LIBFLAGS=-shared -Wl,-soname,libpadding.so
PREFIX=/usr/local/bin

OBJQ = padding.o

%.o: src/%.c
	@echo CC $^
	@$(CC) -fpic -g -c $(CFLAGS) -o $@ $<

libpadding.so: $(OBJQ)
	@echo CC $^
	@$(CC) $(LIBFLAGS) $(CFLAGS) -o $@ $^
	@rm -f *.o

clean:
	@echo Cleaning dir...
	@rm -f *.so *.o
