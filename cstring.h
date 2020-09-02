#ifndef CSTRING_H
#define CSTRING_H

#include <stdlib.h>
#include <string.h>

typedef struct {
    char   *str;
    size_t  len;
    size_t  capacity;
} cstring;

extern cstring cstr_init(const char *);
extern void    cstr_delete(cstring *);
extern void    cstr_assign(cstring *, const char *);
extern void    cstr_append(cstring *, const char *);
extern void    cstr_insert(cstring *, const char *, size_t);
extern void    cstr_push_back(cstring *, char);
extern void    cstr_pop_back(cstring *);
extern void    cstr_replace_char(cstring *, size_t, char);
extern void    cstr_clear(cstring *);
extern int     cstr_exists(const cstring *, const char *);
extern char    cstr_front(const cstring *);
extern char    cstr_back(const cstring *);
extern int     cstr_empty(const cstring *);
extern char   *cstr_copy(const char *);
extern void    cstr_resize(cstring *, size_t);

/* might be useless */
extern int     cstr_equals(const cstring *, const cstring *);
extern int     cstr_not_equals(const cstring *, const cstring *);
extern int     cstr_greater(const cstring *, const cstring *);
extern int     cstr_greater_or_equals(const cstring *, const cstring *);
extern int     cstr_less(const cstring *, const cstring *);
extern int     cstr_less_or_equals(const cstring *, const cstring *);

#endif /* CSTRING_H */
