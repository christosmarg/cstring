# cstring

A simple and lightweight string library for C.

## Usage

Simply include the source files in your projects and compile them
along with your other files.  

When using this library, you must to **always** call the `cstr_init` and `cstr_delete` 
functions whenever you want to make a new instance of `cstring` and stop using it respectively,
in order not to cause any memory leaks, as there's no *constructor* and *destructor* to do it for you.  

The recommended way of initializing an empty string is by doing `cstring foo = cstr_init("")`.

## Functions

* `cstr_init`: Initiliazes string
* `cstr_delete`: Deallocates string
* `cstr_assign`: Assigns a new string to the current string
* `cstr_append`: Appends a string to the current string
* `cstr_insert`: Inserts a string at a specific index
* `cstr_push_back`: Adds a character at the end of the string
* `cstr_pop_back`: Removes the last character in the string
* `cstr_replace_char`: Replaces a character at a specific index
* `cstr_clear`: Erases the whole string
* `cstr_exists`: Checks to see if a (sub)string exists in the string
* `cstr_front`: Returns the first character of the string
* `cstr_back`: Returns the last character of the string
* `cstr_empty`: Checks if the string is empty
* `cstr_copy`: Makes a copy of a given `const char *`
* `cstr_resize`: Resizes the array stored inside the string `struct`
* `cstr_equals`: True if the strings are equal
* `cstr_not_equals`: True if the strings are not equal
* `cstr_greater`: True if the left hand string is greater than the right hand one
* `cstr_greater_or_equals`: True if the left hand string is greater than or equal to the right hand one
* `cstr_less`: True if the left hand string is less than the right hand one
* `cstr_less_or_equals`: True if the left hand string is less than or equal to the right hand one

## Example

See `test.c` for more.

```c
#include <stdio.h>
#include "cstring.h"

int
main(int argc, char **argv)
{
    cstring s = cstr_init("Foo");
    cstr_append(&s, "Bar.");
    printf("%s\n", s.str);
    cstr_delete(&s);

    return 0;
}
```
