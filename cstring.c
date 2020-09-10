#include "cstring.h"

cstring
cstring_create(const char *s)
{
    cstring cs;
    cs.str = cstring_copy(s);
    cs.len = strlen(s);
    cstring_resize(&cs, cs.len << 1); 
    return cs;
}

void
cstring_delete(cstring *cs)
{
    if (!cstring_empty(cs)) free(cs->str);
    cs->str      = NULL;
    cs->len      = 0;
    cs->capacity = 0;
}

void
cstring_assign(cstring *cs, const char *s)
{
    size_t newlen = strlen(s);
    if (!cstring_empty(cs)) free(cs->str);
    cs->str = cstring_copy(s);
    cs->len = newlen;
    if (newlen >= cs->capacity) cstring_resize(cs, newlen << 1);
}

void
cstring_append(cstring *cs, const char *s)
{
    if (!cstring_empty(cs)) {
        size_t newlen = cs->len + strlen(s);
        if (newlen >= cs->capacity) cstring_resize(cs, newlen << 1);
        strcat(cs->str, s);
        cs->len = newlen;
    }
}

void
cstring_insert(cstring *cs, const char *s, size_t i)
{
    if (!cstring_empty(cs) && i < cs->len) {
        size_t slen = strlen(s);
        size_t newlen = cs->len + slen;
        char *tmp1 = (char *)malloc(i + 1);
        char *tmp2 = (char *)malloc(cs->len - i + 1);
        memcpy(tmp1, cs->str, i + 1);
        memcpy(tmp2, cs->str + i, cs->len + 1);
        if (newlen >= cs->capacity) cstring_resize(cs, newlen << 1);
        memcpy(cs->str, tmp1, i + 1);
        memcpy(cs->str + i, s, slen + 1);
        memcpy(cs->str + slen + i, tmp2, cs->len - i + 1);
        cs->len = newlen;
        cs->str[cs->len] = '\0';
        free(tmp1);
        free(tmp2);
    }
}

void
cstring_push_back(cstring *cs, char c)
{
    if (cs->len + 1 >= cs->capacity) cstring_resize(cs, (cs->len + 1) << 1);
    cs->str[cs->len]   = c;
    cs->str[++cs->len] = '\0';
}

void
cstring_pop_back(cstring *cs)
{
    if (cs->len > 0) {
        char *tmp = (char *)malloc(cs->len);
        memcpy(tmp, cs->str, cs->len);
        free(cs->str);
        tmp[cs->len--] = '\0';
        cs->str = tmp;
    }
}

void
cstring_replace_char(cstring *cs, size_t i, char c)
{
    if (i < cs->len) cs->str[i] = c;
}

void
cstring_clear(cstring *cs)
{
    if (!cstring_empty(cs)) free(cs->str);
    cs->str    = (char *)malloc(1);
    cs->str[0] = '\0';
    cs->len    = 0;
}

int
cstring_exists(const cstring *cs, const char *s)
{
    return (strstr(cs->str, s) != NULL);
}

char
cstring_front(const cstring *cs)
{
    return cs->str[0];
}

char
cstring_back(const cstring *cs)
{
    return (!cstring_empty(cs) ? cs->str[cs->len-1] : cs->str[0]);
}

int
cstring_empty(const cstring *cs)
{
    return (cs->str == NULL && cs->len == 0);
}

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
    if (!cstring_empty(cs)) {
        char *tmp = (char *)malloc(newcapacity + 1);
        memcpy(tmp, cs->str, cs->len + 1);
        free(cs->str);
        tmp[cs->len] = '\0';
        cs->str      = tmp;
        cs->capacity = newcapacity;
    }
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

int
cstring_equals(const cstring *lhs, const cstring *rhs)
{
    return (strcmp(lhs->str, rhs->str) == 0);
}

int
cstring_greater(const cstring *lhs, const cstring *rhs)
{
    return (strcmp(lhs->str, rhs->str) > 0);
}

int
cstring_greater_or_equals(const cstring *lhs, const cstring *rhs)
{
    return (strcmp(lhs->str, rhs->str) >= 0);
}

int
cstring_less(const cstring *lhs, const cstring *rhs)
{
    return (strcmp(lhs->str, rhs->str) < 0);
}

int
cstring_less_or_equals(const cstring *lhs, const cstring *rhs)
{
    return (strcmp(lhs->str, rhs->str) <= 0);
}
