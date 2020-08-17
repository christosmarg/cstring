#ifndef CSTRING_H
#define CSTRING_H

#include <stdlib.h>
#include <string.h>

typedef struct {
    char   *str;
    size_t  len;
    size_t  capacity;
} cstring;

extern cstring cstring_init(const char *s);
extern void    cstring_delete(cstring *cs);
extern void    cstring_assign(cstring *cs, const char *s);
extern void    cstring_append(cstring *cs, const char *s);
extern void    cstring_insert(cstring *cs, const char *s, size_t i);
extern void    cstring_push_back(cstring *cs, char c);
extern void    cstring_pop_back(cstring *cs);
extern void    cstring_replace(cstring *cs, size_t i, char c);
extern void    cstring_clear(cstring *cs);
extern int     cstring_exists(const cstring *cs, const char *s);
extern char    cstring_front(const cstring *cs);
extern char    cstring_back(const cstring *cs);
extern int     cstring_empty(const cstring *cs);
extern char   *cstring_copy(const char *s);
extern void    cstring_resize(cstring *cs, size_t n);

/* might be useless */
extern int     cstring_equals(const cstring *lhs, const cstring *rhs);
extern int     cstring_not_equals(const cstring *lhs, const cstring *rhs);
extern int     cstring_greater(const cstring *lhs, const cstring *rhs);
extern int     cstring_greater_or_equals(const cstring *lhs, const cstring *rhs);
extern int     cstring_less(const cstring *lhs, const cstring *rhs);
extern int     cstring_less_or_equals(const cstring *lhs, const cstring *rhs);

#endif /* CSTRING_H */
