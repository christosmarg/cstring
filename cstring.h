#ifndef CSTRING_H
#define CSTRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define CSTRING_NPOS -1
#define CSTRING_OUT_OF_BOUNDS(cs, pos) ((pos) > cs->len)

typedef struct cstring {
    char   *str;
    size_t  len;
    size_t  capacity;
} cstring;

extern cstring  cstring_create(const char *);
extern void     cstring_delete(cstring *);
extern void     cstring_assign(cstring *, const char *);
extern void     cstring_insert(cstring *, const char *, size_t);
extern void     cstring_erase(cstring *, size_t, size_t);
extern void     cstring_erase_matching(cstring *, const char *);
extern void     cstring_erase_all_matching(cstring *, const char *);
extern void     cstring_trim(cstring *, const char *);
extern void     cstring_push_back(cstring *, char);
extern void     cstring_pop_back(cstring *);
extern void     cstring_replace_char(cstring *, size_t, char);
extern void     cstring_replace_str(cstring *, const char *, size_t, size_t);
extern cstring  cstring_substr(const cstring *, size_t, size_t);
extern void     cstring_swap(cstring *, cstring *);
extern void     cstring_clear(cstring *);
extern size_t   cstring_find(const cstring *, const char *);
extern size_t   cstring_rfind(const cstring *, const char *);
extern size_t   cstring_find_first_of(const cstring *, const char *);
extern size_t   cstring_find_first_not_of(const cstring *,const  char *);
extern size_t   cstring_find_last_of(const cstring *, const char *);
extern size_t   cstring_find_last_not_of(const cstring *, const char *);
extern char    *cstring_copy(const char *);
extern void     cstring_resize(cstring *, size_t);
extern cstring *cstring_getline(FILE *, cstring *, char);

/* inlines */
static inline void
cstring_prepend(cstring *cs, const char *s)
{
    cstring_insert(cs, s, 0);
}

static inline void
cstring_append(cstring *cs, const char *s)
{
    cstring_insert(cs, s, cs->len);
}

static inline void
cstring_shrink_to_fit(cstring *cs)
{
    cstring_resize(cs, cs->len);
}

static inline int
cstring_empty(const cstring *cs)
{
    return (cs->str == NULL && cs->len == 0);
}

static inline char
cstring_front(const cstring *cs)
{
    return cs->str[0];
}

static inline char
cstring_back(const cstring *cs)
{
    return (!cstring_empty(cs) ? cs->str[cs->len - 1] : cs->str[0]);
}

static inline int
cstring_starts_with_str(const cstring *cs, const char *s)
{
    return (cstring_find(cs, s) == 0);
}

static inline int
cstring_ends_with_str(const cstring *cs, const char *s)
{
    return (cstring_find(cs, s) == cs->len - strlen(s));
}

static inline int
cstring_starts_with_char(const cstring *cs, char c)
{
    return (cs->str[0] == c);
}

static inline int
cstring_ends_with_char(const cstring *cs, char c)
{
    return (cs->str[cs->len] = c);
}

static inline int
cstring_equal(const cstring *lhs, const cstring *rhs)
{
    return (strcmp(lhs->str, rhs->str) == 0);
}

static inline int
cstring_greater(const cstring *lhs, const cstring *rhs)
{
    return (strcmp(lhs->str, rhs->str) > 0);
}

static inline int
cstring_greater_or_equal(const cstring *lhs, const cstring *rhs)
{
    return (strcmp(lhs->str, rhs->str) >= 0);
}

static inline int
cstring_less(const cstring *lhs, const cstring *rhs)
{
    return (strcmp(lhs->str, rhs->str) < 0);
}

static inline int
cstring_less_or_equal(const cstring *lhs, const cstring *rhs)
{
    return (strcmp(lhs->str, rhs->str) <= 0);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CSTRING_H */
