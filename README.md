# cstring

## Usage

Simply include the source files in your projects and compile them
along with your other files.

## Functions

* `cstring_init`: Initiliazes string
* `cstring_delete`: Deallocates string
* `cstring_assign`: Assigns a new string to the current string
* `cstring_append`: Appends a string to the current string
* `cstring_insert`: Inserts a string at a specific index
* `cstring_push_back`: Adds a character at the end of the string
* `cstring_pop_back`: Removes the last character in the string
* `cstring_replace`: Replaces a character at a specific index
* `cstring_clear`: Erases the whole string
* `cstring_exists`: Checks to see if a (sub)string exists in the string
* `cstring_front`: Returns the first character of the string
* `cstring_back`: Returns the last character of the string
* `cstring_empty`: Checks if the string is empty
* `cstring_copy`: Makes a copy of a given `const char *`
* `cstring_resize`: Resizes the array stored inside the string `struct`
* `cstring_len`: Returns the length of the string
* `cstring_equals`: True if the strings are equal
* `cstring_not_equals`: True if the strings are not equal
* `cstring_greater`: True if the left hand string is greater than the right hand one
* `cstring_greater_or_equals`: True if the left hand string is greater than or equal to the right hand one
* `cstring_less`: True if the left hand string is less than the right hand one
* `cstring_less_or_equals`: True if the left hand string is less than or equal to the right hand one

## Example

A recommended way of using this string is to **always** call the `cstring_delete` function when you're done
working with it, in order not to cause any memory leaks, as there's no *destructor* to do it for you.
See `test.c` for more.

```c
#include <stdio.h>
#include "cstring.h"

int
main(int argc, char **argv)
{
    cstring s = cstring_init("Example string");
    cstring_append(&s, "more text...");
    printf("%s\n", s.str);
    cstring_delete(&s);

    return 0;
}
```
