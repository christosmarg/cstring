#include <stdio.h>
#include "cstring.h"

int
main(int argc, char **argv)
{
    cstring s = cstr_init("Hello world");
    printf("cstr_init: %s (Len: %ld, Capacity: %ld)\n", s.str, s.len, s.capacity);

    cstr_append(&s, "Append");
    printf("cstr_append: %s (Len: %ld, Capacity: %ld)\n", s.str, s.len, s.capacity);

    cstr_assign(&s, "New string");
    printf("cstr_assign: %s (Len: %ld, Capacity: %ld)\n", s.str, s.len, s.capacity);

    if (cstr_exists(&s, "string"))
        printf("cstr_exists: \"string\" exists!\n");

    cstr_push_back(&s, 'c');
    printf("cstr_push_back: %s (Len: %ld, Capacity: %ld)\n", s.str, s.len, s.capacity);

    cstr_insert(&s, "Inserted text", 4);
    printf("cstr_insert: %s (Len: %ld, Capacity: %ld)\n", s.str, s.len, s.capacity);
    
    cstr_pop_back(&s);
    printf("cstr_pop_back: %s (Len: %ld, Capacity: %ld)\n", s.str, s.len, s.capacity);

    cstr_clear(&s);
    printf("cstr_clear: %s (Len: %ld, Capacity: %ld)\n", s.str, s.len, s.capacity);

    cstr_assign(&s, "CSTRING");
    printf("cstr_assign: %s (Len: %ld, Capacity: %ld)\n", s.str, s.len, s.capacity);
    printf("cstr_front: %c\n", cstr_front(&s));
    printf("cstr_back: %c\n", cstr_back(&s));

    cstr_replace(&s, 3, 'x');
    printf("cstr_replace: %s (Len: %ld, Capacity: %ld)\n", s.str, s.len, s.capacity);

    cstr_delete(&s);
    if (cstr_empty(&s)) printf("cstr_delete: Deleted string.\n");

    return 0;
}
