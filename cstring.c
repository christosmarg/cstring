#include "cstring.h"

cstring
cstr_init(const char *s)
{
    cstring cs;
    cs.str = cstr_copy(s);
    cs.len = strlen(s);
    cstr_resize(&cs, cs.len << 1); 
    return cs;
}

void
cstr_delete(cstring *cs)
{
    if (!cstr_empty(cs)) free(cs->str);
    cs->str      = NULL;
    cs->len      = 0;
    cs->capacity = 0;
}

void
cstr_assign(cstring *cs, const char *s)
{
    size_t newlen = strlen(s);
    if (!cstr_empty(cs)) free(cs->str);
    cs->str = cstr_copy(s);
    cs->len = newlen;
    if (newlen >= cs->capacity) cstr_resize(cs, newlen << 1);
}

void
cstr_append(cstring *cs, const char *s)
{
    if (!cstr_empty(cs))
    {
        size_t newlen = cs->len + strlen(s);
        if (newlen >= cs->capacity) cstr_resize(cs, newlen << 1);
        strcat(cs->str, s);
        cs->len = newlen;
    }
}

void
cstr_insert(cstring *cs, const char *s, size_t i)
{
    if (!cstr_empty(cs) && i < cs->len)
    {
        size_t slen = strlen(s);
        size_t newlen = cs->len + slen;
        char *tmp1 = (char *)malloc(i + 1);
        char *tmp2 = (char *)malloc(cs->len - i + 1);
        memcpy(tmp1, cs->str, i + 1);
        memcpy(tmp2, cs->str + i, cs->len + 1);
        if (newlen >= cs->capacity) cstr_resize(cs, newlen << 1);
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
cstr_push_back(cstring *cs, char c)
{
    if (cs->len + 1 >= cs->capacity) cstr_resize(cs, (cs->len + 1) << 1);
    cs->str[cs->len]   = c;
    cs->str[++cs->len] = '\0';
}

void
cstr_pop_back(cstring *cs)
{
    if (cs->len > 0)
    {
        char *tmp = (char *)malloc(cs->len);
        memcpy(tmp, cs->str, cs->len);
        free(cs->str);
        tmp[cs->len--] = '\0';
        cs->str = tmp;
    }
}

void
cstr_replace(cstring *cs, size_t i, char c)
{
    if (i < cs->len) cs->str[i] = c;
}

void
cstr_clear(cstring *cs)
{
    if (!cstr_empty(cs)) free(cs->str);
    cs->str    = (char *)malloc(1);
    cs->str[0] = '\0';
    cs->len    = 0;
}

int
cstr_exists(const cstring *cs, const char *s)
{
    return (strstr(cs->str, s) != NULL);
}

char
cstr_front(const cstring *cs)
{
    return cs->str[0];
}

char
cstr_back(const cstring *cs)
{
    return (!cstr_empty(cs) ? cs->str[cs->len-1] : cs->str[0]);
}

int
cstr_empty(const cstring *cs)
{
    return (cs->str == NULL && cs->len == 0);
}

char *
cstr_copy(const char *s)
{
    size_t len = strlen(s);
    char *tmp = (char *)malloc(len + 1);
    memcpy(tmp, s, len + 1);
    tmp[len] = '\0';
    return tmp;
}

void
cstr_resize(cstring *cs, size_t newcapacity)
{
    if (!cstr_empty(cs))
    {
        char *tmp = (char *)malloc(newcapacity + 1);
        memcpy(tmp, cs->str, cs->len + 1);
        free(cs->str);
        tmp[cs->len] = '\0';
        cs->str      = tmp;
        cs->capacity = newcapacity;
    }
}

int
cstr_equals(const cstring *lhs, const cstring *rhs)
{
    return (strcmp(lhs->str, rhs->str) == 0);
}

int
cstr_greater(const cstring *lhs, const cstring *rhs)
{
    return (strcmp(lhs->str, rhs->str) > 0);
}

int
cstr_greater_or_equals(const cstring *lhs, const cstring *rhs)
{
    return (strcmp(lhs->str, rhs->str) >= 0);
}

int
cstr_less(const cstring *lhs, const cstring *rhs)
{
    return (strcmp(lhs->str, rhs->str) < 0);
}

int
cstr_less_or_equals(const cstring *lhs, const cstring *rhs)
{
    return (strcmp(lhs->str, rhs->str) <= 0);
}
