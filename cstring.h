#ifndef CSTRING_H
#define CSTRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cstring {
    char   *str;
    size_t  len;
    size_t  capacity;
} cstring;

extern cstring  cstring_create(const char *);
extern void     cstring_delete(cstring *);
extern void     cstring_assign(cstring *, const char *);
extern void     cstring_append(cstring *, const char *);
extern void     cstring_insert(cstring *, const char *, size_t);
extern void     cstring_push_back(cstring *, char);
extern void     cstring_pop_back(cstring *);
extern void     cstring_replace_char(cstring *, size_t, char);
extern void     cstring_clear(cstring *);
extern int      cstring_exists(const cstring *, const char *);
extern char     cstring_front(const cstring *);
extern char     cstring_back(const cstring *);
extern int      cstring_empty(const cstring *);
extern char    *cstring_copy(const char *);
extern void     cstring_resize(cstring *, size_t);
extern cstring *cstring_getline(FILE *, cstring *, char);

/* might be useless */
extern int      cstring_equal(const cstring *, const cstring *);
extern int      cstring_not_equal(const cstring *, const cstring *);
extern int      cstring_greater(const cstring *, const cstring *);
extern int      cstring_greater_or_equal(const cstring *, const cstring *);
extern int      cstring_less(const cstring *, const cstring *);
extern int      cstring_less_or_equal(const cstring *, const cstring *);

#endif /* CSTRING_H */
