BIN = cstring
MAN1 = ${BIN}.1
PREFIX = /usr/local
MAN_DIR = ${PREFIX}/man/man1
BIN_DIR = ${PREFIX}bin

SRC = ${wildcard *.c}
OBJ = ${SRC:%.c=%.o}

CC = gcc
CPPFLAGS += -Iinclude -pedantic
CFLAGS += -Wall -std=c99 -O3
LDFLAGS += -Llib
#LDLIBS += 

CP=cp -f
MKDIR = mkdir -p

.PHONY: all clean

all: ${BIN}

${BIN}: ${OBJ}
	${CC} ${LDFLAGS} $^ ${LDLIBS} -o $@

%.o: %.c
	${CC} ${CPPFLAGS} ${CFLAGS} -c $< -o $@

run:
	./${BIN}

#install: all
	#${MKDIR} ${DESTDIR}${BIN_DIR}
	#${CP} ${BIN} ${BIN_DIR}
	#${MKDIR} ${DESTDIR}${MAN_DIR}
	#${CP} ${MAN1} ${DESTDIR}${MAN_DIR}
	#chmod 644 ${DESTDIR}${MAN_DIR}/${MAN1}

clean:
	${RM} ${OBJ} ${BIN}
