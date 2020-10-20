# See LICENSE file for copyright and license details.

LIB = cstring
VERSION = 0.1
DIST = ${LIB}-${VERSION}
MAN3 = ${LIB}.3
PREFIX = /usr/local
MAN_DIR = ${PREFIX}/man/man3
INC_DIR = ${PREFIX}/include
LIB_DIR = ${PREFIX}/lib

EXT = c
#SRC = ${wildcard *.${EXT}}
#OBJ = ${SRC:%.${EXT}=%.o}
SRC = cstring.c
OBJ = cstring.o

AR = ar
ARFLAGS = rs
CC = gcc
INCS = -Iinclude
# Uncomment if you want to compile the library in debug mode
#CPPFLAGS = -DCSTRING_DBG -DVERSION=\"${VERSION}\"
CPPFLAGS = -DVERSION=\"${VERSION}\"
CFLAGS = -Wall -std=c99 -pedantic -O3 ${INCS} ${CPPFLAGS}
LDFLAGS = -Llib

CP = cp -f
RM = rm -f
RM_DIR = rm -rf
MKDIR = mkdir -p
TAR = tar -cf
GZIP = gzip

all: options ${LIB}

options:
	@echo ${LIB} build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

${LIB}: ${OBJ}
	${AR} ${ARFLAGS} lib${LIB}.a ${OBJ}

${OBJ}: ${SRC}
	${CC} ${CFLAGS} -c ${SRC} -o $@

dist: clean
	${MKDIR} ${DIST}
	${CP} -R tests ${SRC} ${MAN3} LICENSE Makefile README.md ${DIST}
	${TAR} ${DIST}.tar ${DIST}
	${GZIP} ${DIST}.tar
	${RM_DIR} ${DIST}

install: all
	${MKDIR} ${DESTDIR}${LIB_DIR} ${DESTDIR}${INC_DIR} ${DESTDIR}${MAN_DIR}
	${CP} ${LIB}.h ${DESTDIR}${INC_DIR}
	${CP} lib${LIB}.a ${DESTDIR}${LIB_DIR}
	${CP} ${MAN3} ${DESTDIR}${MAN_DIR}
	sed "s/VERSION/${VERSION}/g" < ${MAN3} > ${DESTDIR}${MAN_DIR}/${MAN3}
	chmod 755 ${DESTDIR}${INC_DIR}/${LIB}.h
	chmod 644 ${DESTDIR}${LIB_DIR}/lib${LIB}.a
	chmod 644 ${DESTDIR}${MAN_DIR}/${MAN3}

uninstall:
	${RM} ${DESTDIR}${INC_DIR}/${LIB}.h
	${RM} ${DESTDIR}${LIB_DIR}/lib${LIB}.a
	${RM} ${DESTDIR}${MAN_DIR}/${MAN3}

clean:
	${RM} ${LIB} ${OBJ} lib${LIB}.a ${DIST}.tar.gz

.PHONY: all options clean dist install uninstall
