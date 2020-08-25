#ifndef CSTRING_H
#define CSTRING_H

#include <stdlib.h>
#include <string.h>

typedef struct {
    char   *str;
    size_t  len;
    size_t  capacity;
} cstring;

extern cstring cstr_init(const char *s);
extern void    cstr_delete(cstring *cs);
extern void    cstr_assign(cstring *cs, const char *s);
extern void    cstr_append(cstring *cs, const char *s);
extern void    cstr_insert(cstring *cs, const char *s, size_t i);
extern void    cstr_push_back(cstring *cs, char c);
extern void    cstr_pop_back(cstring *cs);
extern void    cstr_replace(cstring *cs, size_t i, char c);
extern void    cstr_clear(cstring *cs);
extern int     cstr_exists(const cstring *cs, const char *s);
extern char    cstr_front(const cstring *cs);
extern char    cstr_back(const cstring *cs);
extern int     cstr_empty(const cstring *cs);
extern char   *cstr_copy(const char *s);
extern void    cstr_resize(cstring *cs, size_t newcapacity);

/* might be useless */
extern int     cstr_equals(const cstring *lhs, const cstring *rhs);
extern int     cstr_not_equals(const cstring *lhs, const cstring *rhs);
extern int     cstr_greater(const cstring *lhs, const cstring *rhs);
extern int     cstr_greater_or_equals(const cstring *lhs, const cstring *rhs);
extern int     cstr_less(const cstring *lhs, const cstring *rhs);
extern int     cstr_less_or_equals(const cstring *lhs, const cstring *rhs);

#endif /* CSTRING_H */
