# See LICENSE file for copyright and license details.
# cstring - a simple and lightweight string library for C
.POSIX:

include config.mk

LIB = cstring
DIST = ${LIB}-${VERSION}
MAN3 = ${LIB}.3

EXT = c
SRC = cstring.c
OBJ = ${SRC:.${EXT}=.o}

all: options ${LIB}

options:
	@echo ${LIB} build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "ARFLAGS  = ${ARFLAGS}"
	@echo "CC       = ${CC}"
	@echo "AR       = ${AR}"

${LIB}: ${OBJ}
	${AR} ${ARFLAGS} lib${LIB}.a ${OBJ}

.${EXT}.o:
	${CC} -c ${CFLAGS} $<

dist: clean
	${MKDIR} ${DIST}
	${CP} -R tests/ config.mk ${MAN3} ${SRC} cstring.h LICENSE Makefile \
		README.md ${DIST}
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
