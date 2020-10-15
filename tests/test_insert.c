#include <stdio.h>
#include <cstring.h>

int
main(int argc, char **argv)
{
    cstring s = cstring_create("HHHHHHEEEEEEEEEEEEEEEEEEEEEYYYYYYYYYYYYYY");
    printf("%s\n", s.str);
    cstring_delete(&s);
    return 0;
}
