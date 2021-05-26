# See LICENSE file for copyright and license details.
# cstring - lightweight string library for C
.POSIX:

include config.mk

LIB = cstring
DIST = ${LIB}-${VERSION}
MAN3 = ${LIB}.3

SRC = cstring.c
OBJ = ${SRC:.c=.o}

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

.c.o:
	${CC} -c ${CFLAGS} $<

dist: clean
	mkdir -p ${DIST}
	cp -R tests config.mk cstring.3 cstring.c cstring.h LICENSE Makefile \
		README ${DIST}
	tar -cf ${DIST}.tar ${DIST}
	gzip ${DIST}.tar
	rm -rf ${DIST}

install: all
	mkdir -p ${DESTDIR}${LIBDIR} ${DESTDIR}${INCDIR} ${DESTDIR}${MANPREFIX}/man3
	cp -f ${LIB}.h ${DESTDIR}${INCDIR}
	cp -f lib${LIB}.a ${DESTDIR}${LIBDIR}
	cp -f ${MAN3} ${DESTDIR}${MANPREFIX}/man3
	sed "s/VERSION/${VERSION}/g" < ${MAN3} > ${DESTDIR}${MANPREFIX}/man3/${MAN3}
	chmod 755 ${DESTDIR}${INC_DIR}/${LIB}.h
	chmod 644 ${DESTDIR}${LIB_DIR}/lib${LIB}.a
	chmod 644 ${DESTDIR}${MANPREFIX}/man3/${MAN3}

uninstall:
	rm -f ${DESTDIR}${INCDIR}/${LIB}.h \
		${DESTDIR}${LIBDIR}/lib${LIB}.a \
		${DESTDIR}${MANPREFIX}/man3/${MAN3}

clean:
	rm -f ${LIB} ${OBJ} lib${LIB}.a ${DIST}.tar.gz *.core

.PHONY: all options clean dist install uninstall
