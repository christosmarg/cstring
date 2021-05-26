# See LICENSE file for copyright and license details.
# cstring version
VERSION = 0.1

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man
INCDIR = ${PREFIX}/include
LIBDIR = ${PREFIX}/lib

# includes and libs
INCS = -Iinclude
LIBS = -Llib

# flags
CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=200809L \
	   -D_XOPEN_SOURCE=700 -DVERSION=\"${VERSION}\"
CFLAGS = -std=c99 -pedantic -Wall -Os ${INCS} ${CPPFLAGS}
LDFLAGS = ${LIBS}
ARFLAGS = rs

# compiler
CC = cc
AR = ar
