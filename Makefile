LIB = cstring
MAN3 = ${LIB}.3
PREFIX = /usr/local
MAN_DIR = ${PREFIX}/man/man3
HDR_DIR = ${PREFIX}/include
LIB_DIR = ${PREFIX}/lib

SRC = ${wildcard *.c}
OBJ = ${SRC:%.c=%.o}

AR = ar
ARFLAGS = rs
CC = gcc
CPPFLAGS += -Iinclude -pedantic
CFLAGS += -Wall -std=c99 -O3
LDFLAGS += -Llib
#LDLIBS += 

CP=cp -f
MKDIR = mkdir -p

.PHONY: all clean

all: ${LIB}

${LIB}: ${OBJ}
	${AR} ${ARFLAGS} lib${LIB}.a ${OBJ}

%.o: %.c
	${CC} ${CPPFLAGS} ${CFLAGS} -c $< -o $@

install: all
	${MKDIR} ${DESTDIR}${LIB_DIR} ${DESTDIR}${HDR_DIR}
	${CP} ${LIB}.h ${DESTDIR}${HDR_DIR}
	${CP} lib${LIB}.a ${DESTDIR}${LIB_DIR}
	chmod 644 ${DESTDIR}${HDR_DIR}/${LIB}.h
	chmod 644 ${DESTDIR}${LIB_DIR}/lib${LIB}.a
	${MKDIR} ${DESTDIR}${MAN_DIR}
	${CP} ${MAN3} ${DESTDIR}${MAN_DIR}
	chmod 644 ${DESTDIR}${MAN_DIR}/${MAN3}

uninstall: all
	sudo ${RM} ${DESTDIR}${HDR_DIR}/${LIB}.h
	sudo ${RM} ${DESTDIR}${LIB_DIR}/lib${LIB}.a
	sudo ${RM} ${DESTDIR}${MAN_DIR}/${MAN3}

clean:
	${RM} ${OBJ} ${LIB} lib${LIB}.a
