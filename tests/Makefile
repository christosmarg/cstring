# See LICENSE file for copyright and license details.
# cstring tests
.POSIX:

BINS = test_basic test_insert
CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -O3
LDFLAGS = -Llib -lcstring

all: options ${BINS}

options:
	@echo "build options:"
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

run:
	for bin in ${BINS}; do \
		echo "---------------------------"; \
		echo "---------------------------"; \
		echo "RUNNING: $${bin}"; \
		echo "---------------------------"; \
		echo "---------------------------"; \
		./$${bin}; \
	done

clean:
	rm -f ${BINS} *.o

test_basic: test_basic.c
	${CC} test_basic.c ${CFLAGS} -o test_basic ${LDFLAGS}

test_insert: test_insert.c
	${CC} test_insert.c ${CFLAGS} -o test_insert ${LDFLAGS}

.PHONY: all options run clean
