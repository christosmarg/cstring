#include <stdio.h>
#include "cstring.h"

int
main(int argc, char **argv)
{
    cstring s = cstring_init("Hello world");
    printf("cstring_init: %s (%ld)\n", s.str, s.len);

    cstring_append(&s, "Append");
    printf("cstring_append: %s (%ld)\n", s.str, s.len);

    cstring_assign(&s, "New string");
    printf("cstring_assign: %s (%ld)\n", s.str, s.len);

    if (cstring_exists(&s, "string"))
        printf("cstring_exists: \"string\" exists!\n");

    cstring_push_back(&s, 'c');
    printf("cstring_push_back: %s (%ld)\n", s.str, s.len);

    cstring_insert(&s, "Inserted text", 4);
    printf("cstring_insert: %s (%ld)\n", s.str, s.len);
    
    cstring_pop_back(&s);
    printf("cstring_pop_back: %s (%ld)\n", s.str, s.len);

    cstring_clear(&s);
    printf("cstring_clear: %s (%ld)\n", s.str, s.len);

    cstring_assign(&s, "CSTRING");
    printf("cstring_assign: %s (%ld)\n", s.str, s.len);
    printf("cstring_front: %c\n", cstring_front(&s));
    printf("cstring_back: %c\n", cstring_back(&s));

    cstring_replace(&s, 3, 'x');
    printf("cstring_replace: %s (%ld)\n", s.str, s.len);

    cstring_delete(&s);
    if (cstring_empty(&s)) printf("cstring_delete: Deleted string.\n");

    return 0;
}
