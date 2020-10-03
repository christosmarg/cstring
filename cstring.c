#include "cstring.h"

#define CSTRING_EXCEEDS_CAPACITY(len, cap)  ((len) >= (cap))

#ifdef CSTRING_DBG
#define CSTRING_FREE(cs) do {                                             \
    CSTRING_DBG_LOG("Before CSTRING_FREE: %s\n", cs->str);                \
    if (!cstring_empty(cs))                                               \
        free(cs->str);                                                    \
} while (0)

/* Might move above erase functions */
#define CSTRING_EXPECTED_ERASE_STR(cs, pos, len) do {                     \
    CSTRING_DBG_LOG("%s", "CSTRING_EXPECTED_ERASE_STR: ");                \
    size_t _i;                                                            \
    for (_i = 0; _i < pos; _i++)                                          \
        printf("%c", cs->str[_i]);                                        \
    for (_i = pos + len; _i < cs->len; _i++)                              \
        printf("%c", cs->str[_i]);                                        \
    printf("\n");                                                         \
} while (0)

#define CSTRING_EXPECTED_ERASE_LEN(cs, len)                               \
    CSTRING_DBG_LOG("CSTRING_EXPECTED_ERASE_LEN: %ld\n", cs->len - len)
#else
#define CSTRING_FREE(cs) do {                                             \
    if (!cstring_empty(cs))                                               \
        free(cs->str);                                                    \
} while (0)
#endif /* CSTRING_DBG */

#define CSTRING_FIND_OCCURENCE(cs, s, func) do {                          \
    char *_found;                                                         \
    if ((_found = func(cs->str, (s))) != NULL)                            \
        return (_found - cs->str);                                        \
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
    if (!CSTRING_OUT_OF_BOUNDS(cs, i) && s != NULL) {
        size_t slen = strlen(s);
        size_t newlen = cs->len + slen;
        char *tmp;
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

void
cstring_erase(cstring *cs, size_t pos, size_t len)
{
    if (!cstring_empty(cs)
    &&  !CSTRING_OUT_OF_BOUNDS(cs, pos)
    &&  !CSTRING_OUT_OF_BOUNDS(cs, len))
    {
#ifdef CSTRING_DBG
        CSTRING_DBG_LOG("STR: %s | INDEX: %ld | LEN: %ld\n", cs->str, pos, len);
        CSTRING_EXPECTED_ERASE_STR(cs, pos, len);
        CSTRING_EXPECTED_ERASE_LEN(cs, len);
#endif /* CSTRING_DBG */
        size_t newlen = cs->len - len;
        char *tmp;
        CSTRING_MALLOC(tmp, newlen + 1);
        memcpy(tmp, cs->str, pos);
        memcpy(tmp + pos, cs->str + pos + len, cs->len - len + pos);
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
    CSTRING_FREE(cs);
    CSTRING_MALLOC(cs->str, 1);
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
    char *tmp;
    CSTRING_MALLOC(tmp, len + 1);
    memcpy(tmp, s, len + 1);
    tmp[len] = '\0'; /* Add \0 in case s didn't have it */
    return tmp;
}

void
cstring_resize(cstring *cs, size_t newcapacity)
{
#ifdef CSTRING_DBG
    CSTRING_DBG_LOG("Old capacity: %ld | New capacity: %ld\n",
            cs->capacity, newcapacity);
#endif /* CSTRING_DBG */
    char *tmp;
    CSTRING_MALLOC(tmp, newcapacity);
    memcpy(tmp, cs->str, cs->len + 1); /* copy \0 too */
    CSTRING_FREE(cs);
    cs->str = tmp;
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
        if (c == delim) break;
        else cstring_push_back(cs, c);
    }
    return (c == EOF) ? NULL : cs;
}
