#include <stdio.h>
#include "cstring.h"

int
main(int argc, char **argv)
{
    cstring s = cstring_init("Hello world");
    printf("cstring_init: %s (Len: %ld, Capacity: %ld)\n", s.str, s.len, s.capacity);

    cstring_append(&s, "Append");
    printf("cstring_append: %s (Len: %ld, Capacity: %ld)\n", s.str, s.len, s.capacity);

    cstring_assign(&s, "New string");
    printf("cstring_assign: %s (Len: %ld, Capacity: %ld)\n", s.str, s.len, s.capacity);

    if (cstring_exists(&s, "string"))
        printf("cstring_exists: \"string\" exists!\n");

    cstring_push_back(&s, 'c');
    printf("cstring_push_back: %s (Len: %ld, Capacity: %ld)\n", s.str, s.len, s.capacity);

    cstring_insert(&s, "Inserted text", 4);
    printf("cstring_insert: %s (Len: %ld, Capacity: %ld)\n", s.str, s.len, s.capacity);
    
    cstring_pop_back(&s);
    printf("cstring_pop_back: %s (Len: %ld, Capacity: %ld)\n", s.str, s.len, s.capacity);

    cstring_clear(&s);
    printf("cstring_clear: %s (Len: %ld, Capacity: %ld)\n", s.str, s.len, s.capacity);

    cstring_assign(&s, "CSTRING");
    printf("cstring_assign: %s (Len: %ld, Capacity: %ld)\n", s.str, s.len, s.capacity);
    printf("cstring_front: %c\n", cstring_front(&s));
    printf("cstring_back: %c\n", cstring_back(&s));

    cstring_replace_char(&s, 3, 'x');
    printf("cstring_replace: %s (Len: %ld, Capacity: %ld)\n", s.str, s.len, s.capacity);

    cstring_delete(&s);
    if (cstring_empty(&s)) printf("cstring_delete: Deleted string.\n");

    return 0;
}
