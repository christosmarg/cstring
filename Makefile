LIB = cstring
VERSION = 0.1
DIST = ${BIN}-${VERSION}
MAN3 = ${LIB}.3
PREFIX = /usr/local
MAN_DIR = ${PREFIX}/man/man3
HDR_DIR = ${PREFIX}/include
LIB_DIR = ${PREFIX}/lib

EXT = c
SRC = ${wildcard *.${EXT}}
OBJ = ${SRC:%.${EXT}=%.o}

AR = ar
ARFLAGS = rs
CC = gcc
CPPFLAGS += -Iinclude -DCSTRING_DBG -DVERSION=\"${VERSION}\"
#CPPFLAGS += -Iinclude -DVERSION=\"${VERSION}\"
CFLAGS += -Wall -std=c99 -pedantic -O3
LDFLAGS += -Llib
#LDLIBS += 

CP = cp -f
RM = rm -f
RM_DIR = rm -rf
MKDIR = mkdir -p
TAR = tar -cf
GZIP = gzip

all: ${LIB}

${LIB}: ${OBJ}
	${AR} ${ARFLAGS} lib${LIB}.a ${OBJ}

%.o: %.${EXT}
	${CC} ${CPPFLAGS} ${CFLAGS} -c $< -o $@

dist: clean
	${MKDIR} ${DIST}
	${CP} -R tests ${SRC} ${MAN3} cstring.h Makefile README.md ${DIST}
	${TAR} ${DIST}.tar ${DIST}
	${GZIP} ${DIST}.tar
	${RM_DIR} ${DIST}

install: all
	${MKDIR} ${DESTDIR}${LIB_DIR} ${DESTDIR}${HDR_DIR} ${DESTDIR}${MAN_DIR}
	${CP} ${LIB}.h ${DESTDIR}${HDR_DIR}
	${CP} lib${LIB}.a ${DESTDIR}${LIB_DIR}
	${CP} ${MAN3} ${DESTDIR}${MAN_DIR}
	sed "s/VERSION/${VERSION}/g" < ${MAN3} > ${DESTDIR}${MAN_DIR}/${MAN3}
	chmod 644 ${DESTDIR}${HDR_DIR}/${LIB}.h
	chmod 644 ${DESTDIR}${LIB_DIR}/lib${LIB}.a
	chmod 644 ${DESTDIR}${MAN_DIR}/${MAN3}

uninstall: all
	${RM} ${DESTDIR}${HDR_DIR}/${LIB}.h
	${RM} ${DESTDIR}${LIB_DIR}/lib${LIB}.a
	${RM} ${DESTDIR}${MAN_DIR}/${MAN3}

clean:
	${RM} ${OBJ} ${LIB} lib${LIB}.a

.PHONY: all clean dist install uninstall
