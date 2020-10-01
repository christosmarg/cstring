#include "cstring.h"

#define CSTRING_EXCEEDS_CAPACITY(len, cap)  ((len) >= (cap))
#define CSTRING_FIND_OCCURENCE(cs, s, func) do { \
    char *_found;                                \
    if ((_found = func(cs->str, (s))) != NULL)   \
        return (_found - cs->str);               \
} while (0)

static int
cstring_is_one_of(char c, const char *s)
{
    for (; *s; s++)
        if (*s == c)
            return 1;
    return 0;
}

cstring
cstring_create(const char *s)
{
    cstring cs;
    cs.len = strlen(s);
    cs.str = cstring_copy(s);
    cstring_resize(&cs, cs.len << 1);
    return cs;
}

void
cstring_delete(cstring *cs)
{
    if (!cstring_empty(cs)) free(cs->str);
    cs->str = NULL;
    cs->len = 0;
    cs->capacity = 0;
}

void
cstring_assign(cstring *cs, const char *s)
{
    size_t newlen = strlen(s);
    if (CSTRING_EXCEEDS_CAPACITY(newlen, cs->capacity))
        cstring_resize(cs, newlen << 1);
    if (!cstring_empty(cs)) free(cs->str);
    cs->str = cstring_copy(s);
    cs->len = newlen;
}

void
cstring_insert(cstring *cs, const char *s, size_t i)
{
    if (!CSTRING_OUT_OF_BOUNDS(cs, i) && s != NULL) {
        size_t slen = strlen(s);
        size_t newlen = cs->len + slen;
        char *tmp = (char *)malloc(newlen + 1);
        memcpy(tmp, cs->str, i);
        memcpy(tmp + i, s, slen);
        memcpy(tmp + slen + i, cs->str + i , newlen - slen - i);
        if (CSTRING_EXCEEDS_CAPACITY(newlen, cs->capacity))
            cstring_resize(cs, newlen << 1);
        free(cs->str);
        cs->len = newlen;
        cs->str = tmp;
        cs->str[cs->len] = '\0';
    }
}

void
cstring_erase(cstring *cs, size_t pos, size_t len)
{
    if (!cstring_empty(cs)
    &&  !CSTRING_OUT_OF_BOUNDS(cs, pos)
    &&  !CSTRING_OUT_OF_BOUNDS(cs, len))
    {
        size_t newlen = cs->len - len;
        char *tmp = (char *)malloc(newlen + 1);
        memcpy(tmp, cs->str, pos); // pos + 1??
        memcpy(tmp + pos, cs->str + pos + len, newlen);
        free(cs->str);
        cs->len = newlen;
        cs->str = tmp;
        cs->str[cs->len] = '\0';
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
    if (s != NULL) {
        size_t len = strlen(s);
        size_t i = cstring_find(cs, s);
        for (; i != CSTRING_NPOS; i = cstring_find(cs, s))
            cstring_erase(cs, i, len);
    }
}

void
cstring_trim(cstring *cs, const char *s)
{
    size_t i = cstring_find_first_of(cs, s);
    for (; i != CSTRING_NPOS; i = cstring_find_first_of(cs, s))
        cstring_erase(cs, i, 1);
}

void
cstring_push_back(cstring *cs, char c)
{
    if (CSTRING_EXCEEDS_CAPACITY(cs->len, cs->capacity))
        cstring_resize(cs, cs->len << 1);
    cs->str[cs->len] = c;
    cs->str[++cs->len] = '\0';
}

void
cstring_pop_back(cstring *cs)
{
    if (cs->len > 0) {
        char *tmp = (char *)malloc(cs->len);
        memcpy(tmp, cs->str, cs->len);
        free(cs->str);
        tmp[--cs->len] = '\0';
        cs->str = tmp;
    }
}

void
cstring_replace_char(cstring *cs, size_t i, char c)
{
    if (!CSTRING_OUT_OF_BOUNDS(cs, i))
        cs->str[i] = c;
}

void
cstring_replace_str(cstring *cs, const char *s, size_t pos, size_t len)
{
    if (!CSTRING_OUT_OF_BOUNDS(cs, pos)
    &&  !CSTRING_OUT_OF_BOUNDS(cs, len)
    &&  !CSTRING_OUT_OF_BOUNDS(cs, pos + len))
    {
        int i = pos;
        for (; i < len && *s; s++, i++)
            cs->str[i] = *s;
    }
}

cstring
cstring_substr(const cstring *cs, size_t pos, size_t len)
{
    if (CSTRING_OUT_OF_BOUNDS(cs, pos)
    ||  CSTRING_OUT_OF_BOUNDS(cs, len))
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
cstring_clear(cstring *cs)
{
    if (!cstring_empty(cs)) free(cs->str);
    cs->str = (char *)malloc(1);
    cs->str[0] = '\0';
    cs->len = 0;
    cs->capacity = 0;
}

#define CSTRING_CHECK(cs, s)      \
    if (cstring_empty(cs) || !*s) \
        return CSTRING_NPOS

size_t
cstring_find(const cstring *cs, const char *s)
{
    CSTRING_CHECK(cs, s);
    CSTRING_FIND_OCCURENCE(cs, s, strstr);
    return CSTRING_NPOS;
}

size_t
cstring_rfind(const cstring *cs, const char *s)
{
    CSTRING_CHECK(cs, s);
    /* SIMPLIFY */
    int found;
    size_t idx = -1;
    size_t slen = strlen(s);
    size_t  i = 0, j;
    for (; i <= cs->len - slen; i++) {
        found = 1;
        for (j = 0; j < slen; j++) {
            if (cs->str[i + j] != s[j]) {
                found = 0;
                break;
            }
        }
        if (found) idx = i;
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
    CSTRING_CHECK(cs, s);
    size_t i = 0;
    for (; i < cs->len; i++)
        if (!cstring_is_one_of(cs->str[i], s))
            return i;
    return CSTRING_NPOS;
}

size_t
cstring_find_last_of(const cstring *cs, const char *s)
{
    CSTRING_CHECK(cs, s);
    size_t i = *(s + strlen(s));
    for (; i >= 0; i--) {
        CSTRING_FIND_OCCURENCE(cs, s[i], strrchr);
    }
    return CSTRING_NPOS;
}

size_t
cstring_find_last_not_of(const cstring *cs, const char *s)
{
    CSTRING_CHECK(cs, s);
    size_t i = cs->len;
    for (; i >= 0; i--)
        if (!cstring_is_one_of(cs->str[i], s))
            return i;
    return CSTRING_NPOS;
}

#undef CSTR_CHECK

char *
cstring_copy(const char *s)
{
    size_t len = strlen(s);
    char *tmp = (char *)malloc(len + 1);
    memcpy(tmp, s, len + 1);
    tmp[len] = '\0';
    return tmp;
}

void
cstring_resize(cstring *cs, size_t newcapacity)
{
    cs->str = (char *)realloc(cs->str, newcapacity);
    cs->capacity = newcapacity;
}

cstring *
cstring_getline(FILE *fd, cstring *cs, char delim)
{
    char c;
    cstring_clear(cs);
    while ((c = fgetc(fd)) != EOF && c != '\n') {
        if (c == delim) break;
        else cstring_push_back(cs, c);
    }
    return (c == EOF) ? NULL : cs;
}
