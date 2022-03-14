/* See LICENSE file for copyright and license details. */
#ifndef _CSTRING_H_
#define _CSTRING_H_

#ifdef __cplusplus
"C" {
#endif /* __cplusplus */

#define CSTRING_NPOS -1
#define CSTRING_INIT_EMPTY ""
#define CSTRING_OUT_OF_BOUNDS(len, pos) ((pos) > (len))
#define CSTRING_ARR_LEN(x) (sizeof((x)) / sizeof((x)[0]))

typedef struct _cstring {
	size_t len;			/* strlen of str */
	size_t capacity;		/* total capacity of the array */
	char *str;			/* the string */

#define CSTRING_SORT_ASCENDING 0x01	/* sort in ascending order */
#define CSTRING_SORT_DESCENDING 0x02	/* sort in descending order */
#define CSTRING_SORT_CALLBACK 0x04	/* sort using a callback function */
#define CSTRING_SORT_REST 0x10		/* sort the rest of the array */
} cstring;

typedef int (*cstring_sort_callback)(const void *, const void *);

cstring cstring_create(const char *);
void cstring_delete(cstring *);
void cstring_assign(cstring *, const char *);
void cstring_insert(cstring *, const char *, size_t);
void cstring_erase(cstring *, size_t, size_t);
void cstring_erase_matching(cstring *, const char *);
void cstring_erase_all_matching(cstring *, const char *);
void cstring_trim(cstring *, const char *);
void cstring_push_back(cstring *, char);
void cstring_pop_back(cstring *);
void cstring_replace_char(cstring *, size_t, char);
void cstring_replace_str(cstring *, const char *, size_t, size_t);
cstring cstring_substr(const cstring *, size_t, size_t);
void cstring_swap(cstring *, cstring *);
void cstring_sort_partial(cstring *, size_t, size_t, int, cstring_sort_callback);
void cstring_sort_chars_partial(cstring *cs, size_t, size_t, int, cstring_sort_callback);
void cstring_clear(cstring *);
size_t cstring_find(const cstring *, const char *);
size_t cstring_rfind(const cstring *, const char *);
size_t cstring_find_first_of(const cstring *, const char *);
size_t cstring_find_first_not_of(const cstring *,const  char *);
size_t cstring_find_last_of(const cstring *, const char *);
size_t cstring_find_last_not_of(const cstring *, const char *);
int cstring_ends_with_str(const cstring *, const char *);
char *cstring_copy(const char *);
void cstring_resize(cstring *, size_t);
cstring *cstring_getline(FILE *, cstring *, char);

/* static inlines */
static inline void cstring_prepend(cstring *, const char *);
static inline void cstring_append(cstring *, const char *);
static inline void cstring_sort(cstring *, size_t, int, cstring_sort_callback);
static inline void cstring_sort_chars(cstring *, int, cstring_sort_callback);
static inline void cstring_shrink_to_fit(cstring *);
static inline int cstring_empty(const cstring *);
static inline char cstring_front(const cstring *);
static inline char cstring_back(const cstring *);
static inline int cstring_starts_with_str(const cstring *, const char *);
static inline int cstring_starts_with_char(const cstring *, char);
static inline int cstring_ends_with_char(const cstring *, char);
static inline void *cstring_data(const cstring *);
static inline int cstring_equal(const cstring *, const cstring *);
static inline int cstring_greater(const cstring *, const cstring *);
static inline int cstring_greater_or_equal(const cstring *, const cstring *);
static inline int cstring_less(const cstring *, const cstring *);
static inline int cstring_less_or_equal(const cstring *, const cstring *);

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
cstring_sort(cstring *cs, size_t len, int flags, cstring_sort_callback cb)
{
	cstring_sort_partial(cs, 0, len, flags, cb);
}

static inline void
cstring_sort_chars(cstring *cs, int flags, cstring_sort_callback cb)
{
	cstring_sort_chars_partial(cs, 0, cs->len, flags, cb);
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
	return (cs->str[0]);
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
cstring_starts_with_char(const cstring *cs, char c)
{
	return (cs->str[0] == c);
}

static inline int
cstring_ends_with_char(const cstring *cs, char c)
{
	return (cs->str[cs->len] == c);
}

static inline void *
cstring_data(const cstring *cs)
{
	return ((void *)cs->str);
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

#endif /* _CSTRING_H_ */
