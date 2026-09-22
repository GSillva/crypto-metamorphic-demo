CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Werror -O2

.PHONY: all test clean

all: metamorphic_test

metamorphic_test: src/kem.c src/kem.h tests/metamorphic_test.c
	$(CC) $(CFLAGS) -Isrc src/kem.c tests/metamorphic_test.c -o metamorphic_test

test: metamorphic_test
	./metamorphic_test

clean:
	rm -f metamorphic_test
