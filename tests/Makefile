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
	@echo "---------------------------"
	@echo "---------------------------"
	@echo "RUNNING: test_basic"
	@echo "---------------------------"
	@echo "---------------------------"
	./test_basic
	
	@echo "---------------------------"
	@echo "---------------------------"
	@echo "RUNNING: test_insert"
	@echo "---------------------------"
	@echo "---------------------------"
	./test_insert

clean:
	rm -f ${BINS} *.o

test_basic: test_basic.c
	${CC} test_basic.c ${CFLAGS} -o test_basic ${LDFLAGS}

test_insert: test_insert.c
	${CC} test_insert.c ${CFLAGS} -o test_insert ${LDFLAGS}

.PHONY: all options run clean
