/* See LICENSE file for copyright and license details. */
#include "cstring.h"

#define CSTRING_EXCEEDS_CAPACITY(len, cap) ((len) >= (cap))

#define CSTRING_FIND_OCCURENCE(cs, s, func) do {	       \
	char *_found;					       \
	if ((_found = func(cs->str, (s))) != NULL)	       \
		return (_found - cs->str);		       \
} while (0)

#ifdef CSTRING_DBG
#define CSTRING_FREE(cs) do {				       \
	CSTRING_DBG_LOG("Before CSTRING_FREE: %s\n", cs->str); \
	if (!cstring_empty(cs))				       \
		free(cs->str);				       \
} while (0)
#else /* !CSTRING_DBG */
#define CSTRING_FREE(cs) do {				       \
	if (!cstring_empty(cs))				       \
		free(cs->str);				       \
} while (0)
#endif /* CSTRING_DBG */

/* statics */
static int cstring_is_one_of(char, const char *);
static inline int cstring_cmp_greater(const void *, const void *);
static inline int cstring_cmp_less(const void *, const void *);
static inline int cstring_cmp_char_greater(const void *, const void *);
static inline int cstring_cmp_char_less(const void *, const void *);

static int
cstring_is_one_of(char c, const char *s)
{
	for (; *s; s++)
		if (*s == c)
			return 1;
	return 0;
}

static inline int
cstring_cmp_greater(const void *lhs, const void *rhs)
{
	return cstring_greater((cstring *)lhs, (cstring *)rhs);
}

static inline int
cstring_cmp_less(const void *lhs, const void *rhs)
{
	return cstring_less((cstring *)lhs, (cstring *)rhs);
}

static inline int
cstring_cmp_char_greater(const void *lhs, const void *rhs)
{
	return (*(char *)lhs - *(char *)rhs);
}

static inline int
cstring_cmp_char_less(const void *lhs, const void *rhs)
{
	return -(*(char *)lhs - *(char *)rhs);
}

/* externs */
cstring
cstring_create(const char *s)
{
	cstring cs;
	cs.len = strlen(s);
	cs.str = cstring_copy(s);
	cstring_resize(&cs, cs.len << 1);
#ifdef CSTRING_DBG
	CSTRING_DBG_LOG_STR_INFO(s, cs.len);
	CSTRING_DBG_LOG_CSTR_INFO_NPTR(cs);
#endif /* CSTRING_DBG */
	return cs;
}

void
cstring_delete(cstring *cs)
{
	CSTRING_FREE(cs);
	cs->str = NULL;
	cs->len = 0;
	cs->capacity = 0;
}

void
cstring_assign(cstring *cs, const char *s)
{
	CSTRING_FREE(cs);
	cs->str = cstring_copy(s);
	cs->len = strlen(s);
	if (CSTRING_EXCEEDS_CAPACITY(cs->len, cs->capacity))
		cstring_resize(cs, cs->len << 1);
#ifdef CSTRING_DBG
	CSTRING_DBG_LOG_STR_INFO(s, cs->len);
	CSTRING_DBG_LOG_CSTR_INFO(cs);
#endif /* CSTRING_DBG */
}

void
cstring_insert(cstring *cs, const char *s, size_t i)
{
	size_t slen, newlen;
	char *tmp;

	if (!CSTRING_OUT_OF_BOUNDS(cs->len, i) && s != NULL) {
		slen = strlen(s);
		newlen = cs->len + slen;
		CSTRING_MALLOC(tmp, newlen + 1);
		memcpy(tmp, cs->str, i);
		memcpy(tmp + i, s, slen);
		memcpy(tmp + i + slen, cs->str + i, newlen - slen - i + 1);
		CSTRING_FREE(cs);
		cs->len = newlen;
		cs->str = tmp;
		cs->str[cs->len] = '\0';
		if (CSTRING_EXCEEDS_CAPACITY(newlen, cs->capacity))
			cstring_resize(cs, newlen << 1);
#ifdef CSTRING_DBG
		CSTRING_DBG_LOG_STR_INFO(s, slen);
		CSTRING_DBG_LOG_CSTR_INFO(cs);
#endif /* CSTRING_DBG */
	}
}

#ifdef CSTRING_DBG
// FIXME
#define CSTRING_DBG_EXPECTED_ERASE_STR(cs, pos, len) do {		    \
	CSTRING_DBG_LOG("%s", "CSTRING_DBG_EXPECTED_ERASE_STR: ");	    \
	size_t _i;							    \
	for (_i = 0; _i < (pos); _i++)					    \
		printf("%c", cs->str[_i]);				    \
	for (_i = (pos) + (len); _i < cs->len; _i++)			    \
		printf("%c", cs->str[_i]);				    \
	printf("\n");							    \
} while (0)

#define CSTRING_DBG_EXPECTED_ERASE_LEN(cs, len)				    \
	CSTRING_DBG_LOG("CSTRING_DBG_EXPECTED_ERASE_LEN: %ld\n", cs->len - len)
#endif /* CSTRING_DBG */

void
cstring_erase(cstring *cs, size_t pos, size_t len)
{
	size_t newlen;
	char *tmp;

	if (!cstring_empty(cs)
	&& (!CSTRING_OUT_OF_BOUNDS(cs->len, pos)
	||  !CSTRING_OUT_OF_BOUNDS(cs->len, len))) {
#ifdef CSTRING_DBG
		CSTRING_DBG_LOG("STR: %s | INDEX: %ld | LEN: %ld\n",
				cs->str, pos, len);
		CSTRING_DBG_EXPECTED_ERASE_STR(cs, pos, len);
		CSTRING_DBG_EXPECTED_ERASE_LEN(cs, len);
#endif /* CSTRING_DBG */
		newlen = cs->len - len;
		CSTRING_MALLOC(tmp, newlen + 1);
		memcpy(tmp, cs->str, pos);
		memcpy(tmp + pos, cs->str + pos + len, cs->len - pos - len);
		CSTRING_FREE(cs); /* Useless check but keep it for consistency */
		cs->len = newlen;
		cs->str = tmp;
		cs->str[cs->len] = '\0';
#ifdef CSTRING_DBG
		CSTRING_DBG_LOG_CSTR_INFO(cs);
#endif /* CSTRING_DBG */
	}
}

void
cstring_erase_matching(cstring *cs, const char *s)
{
	if (s != NULL)
		cstring_erase(cs, cstring_find(cs, s), strlen(s));
}

void
cstring_erase_all_matching(cstring *cs, const char *s)
{
	size_t len, i;

	if (s != NULL) {
		len = strlen(s);
		i = cstring_find(cs, s);
		for (; i != CSTRING_NPOS; i = cstring_find(cs, s))
			cstring_erase(cs, i, len);
	}
}

void
cstring_trim(cstring *cs, const char *s)
{
	size_t i;
	
	i = cstring_find_first_of(cs, s);
	for (; i != CSTRING_NPOS; i = cstring_find_first_of(cs, s))
		cstring_erase(cs, i, 1);
}

#ifdef CSTRING_DBG
#undef CSTRING_DBG_EXPECTED_ERASE_STR
#undef CSTRING_DBG_EXPECTED_ERASE_LEN
#endif /* CSTRING_DBG */

void
cstring_push_back(cstring *cs, char c)
{
	if (CSTRING_EXCEEDS_CAPACITY(cs->len, cs->capacity))
		cstring_resize(cs, cs->len << 1);
	cs->str[cs->len] = c;
	cs->str[++cs->len] = '\0';
#ifdef CSTRING_DBG
	CSTRING_DBG_LOG_CSTR_INFO(cs);
#endif /* CSTRING_DBG */
}

void
cstring_pop_back(cstring *cs)
{
	if (cs->len > 0)
		cs->str[--cs->len] = '\0';
}

void
cstring_replace_char(cstring *cs, size_t i, char c)
{
	if (!CSTRING_OUT_OF_BOUNDS(cs->len, i))
		cs->str[i] = c;
}

void
cstring_replace_str(cstring *cs, const char *s, size_t pos, size_t olen)
{
	if (!CSTRING_OUT_OF_BOUNDS(cs->len, pos)
	&&  !CSTRING_OUT_OF_BOUNDS(cs->len, olen)) {
		cstring_erase(cs, pos, olen);
		cstring_insert(cs, s, pos);
	}
}

cstring
cstring_substr(const cstring *cs, size_t pos, size_t len)
{
	if (CSTRING_OUT_OF_BOUNDS(cs->len, pos)
	||  CSTRING_OUT_OF_BOUNDS(cs->len, len))
		return cstring_create("");
	cstring substr = cstring_create(&cs->str[pos]);
	substr.len = len;
	substr.str[len] = '\0';
	cstring_shrink_to_fit(&substr);
	return substr;
}

void
cstring_swap(cstring *lhs, cstring *rhs)
{
	cstring tmp = *lhs;
	*lhs = *rhs;
	*rhs = tmp;
}

void
cstring_sort_partial(cstring *cs, size_t pos, size_t len, int flags,
		     cstring_sort_callback cb)
{
	if (flags & CSTRING_SORT_REST ||  CSTRING_OUT_OF_BOUNDS(len, pos + len))
		len -= pos;

	if (flags & CSTRING_SORT_ASCENDING)
		qsort(cs + pos, len, sizeof(cstring), cstring_cmp_greater);
	else if (flags & CSTRING_SORT_DESCENDING)
		qsort(cs + pos, len, sizeof(cstring), cstring_cmp_less);
	else if (flags & CSTRING_SORT_CALLBACK)
		qsort(cs + pos, len, sizeof(cstring), cb);
}

void
cstring_sort_chars_partial(cstring *cs, size_t pos, size_t len, int flags,
			   cstring_sort_callback cb)
{
	if (flags & CSTRING_SORT_REST ||  CSTRING_OUT_OF_BOUNDS(cs->len, pos + len))
		len = cs->len - pos;

	if (flags & CSTRING_SORT_ASCENDING)
		qsort(cs->str + pos, len, sizeof(char), cstring_cmp_char_greater);
	else if (flags & CSTRING_SORT_DESCENDING)
		qsort(cs->str + pos, len, sizeof(char), cstring_cmp_char_less);
	else if (flags & CSTRING_SORT_CALLBACK)
		qsort(cs->str + pos, len, sizeof(char), cb);
}

void
cstring_clear(cstring *cs)
{
	CSTRING_FREE(cs);
	CSTRING_MALLOC(cs->str, 1);
	cs->str[0] = '\0';
	cs->len = 0;
	cs->capacity = 0;
}

#define CSTRING_CHECK(cs, s)		\
	if (cstring_empty(cs) || !*(s)) \
		return CSTRING_NPOS

size_t
cstring_find(const cstring *cs, const char *s)
{
	CSTRING_CHECK(cs, s);
	CSTRING_FIND_OCCURENCE(cs, s, strstr);
	return CSTRING_NPOS;
}

/*SIMPLIFY */
size_t
cstring_rfind(const cstring *cs, const char *s)
{
	size_t idx, slen, i, j;
	int found;

	CSTRING_CHECK(cs, s);
	idx = -1;
	slen = strlen(s);
	for (i = 0; i <= cs->len - slen; i++) {
		found = 1;
		for (j = 0; j < slen; j++) {
			if (cs->str[i + j] != s[j]) {
				found = 0;
				break;
			}
		}
		if (found)
			idx = i;
	}
	return (idx == -1 ? CSTRING_NPOS : idx);
}

size_t
cstring_find_first_of(const cstring *cs, const char *s)
{
	CSTRING_CHECK(cs, s);
	for (; *s; s++) {
		CSTRING_FIND_OCCURENCE(cs, *s, strchr);
	}
	return CSTRING_NPOS;
}

size_t
cstring_find_first_not_of(const cstring *cs, const char *s)
{
	size_t i = 0;

	CSTRING_CHECK(cs, s);
	for (; i < cs->len; i++)
		if (!cstring_is_one_of(cs->str[i], s))
			return i;
	return CSTRING_NPOS;
}

size_t
cstring_find_last_of(const cstring *cs, const char *s)
{
	size_t i;

	CSTRING_CHECK(cs, s);
	i = *(s + strlen(s));
	for (; i >= 0; i--) {
		CSTRING_FIND_OCCURENCE(cs, s[i], strrchr);
	}
	return CSTRING_NPOS;
}

size_t
cstring_find_last_not_of(const cstring *cs, const char *s)
{
	size_t i = cs->len;

	CSTRING_CHECK(cs, s);
	for (; i >= 0; i--)
		if (!cstring_is_one_of(cs->str[i], s))
			return i;
	return CSTRING_NPOS;
}

#undef CSTR_CHECK

int
cstring_ends_with_str(const cstring *cs, const char *s)
{
	/* avoid cstring_substr */
	cstring sub;
	size_t slen;
	int found;

	slen = strlen(s);
	sub = cstring_substr(cs, cs->len - slen, slen);
	found = !strcmp(sub.str, s);
	cstring_delete(&sub);
	return found;
}

char *
cstring_copy(const char *s)
{
	size_t len;
	char *tmp;

	len = strlen(s);
	CSTRING_MALLOC(tmp, len + 1);
	memcpy(tmp, s, len + 1);
	tmp[len] = '\0'; /* Add \0 in case s didn't have it */
	return tmp;
}

void
cstring_resize(cstring *cs, size_t newcapacity)
{
	char *tmp;

#ifdef CSTRING_DBG
	CSTRING_DBG_LOG("Old capacity: %ld | New capacity: %ld\n",
			cs->capacity, newcapacity);
#endif /* CSTRING_DBG */
	CSTRING_MALLOC(tmp, newcapacity + 1); /* no +1? */
	memcpy(tmp, cs->str, cs->len + 1);    /* copy \0 too */
	CSTRING_FREE(cs);
	cs->str = tmp;
	cs->str[cs->len] = '\0';
	cs->capacity = newcapacity;
#ifdef CSTRING_DBG
	CSTRING_DBG_LOG_CSTR_INFO(cs);
#endif /* CSTRING_DBG */
}

cstring *
cstring_getline(FILE *fd, cstring *cs, char delim)
{
	char c;

	cstring_clear(cs);
	while ((c = fgetc(fd)) != EOF && c != '\n') {
		if (c == delim)
			break;
		else
			cstring_push_back(cs, c);
	}
	return (c == EOF) ? NULL : cs;
}
