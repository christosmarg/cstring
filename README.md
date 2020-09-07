# cstring

A simple and lightweight string library for C.

## Usage

Simply include the source files in your projects and compile them
along with your other files.  

When using this library, you must to **always** call the `cstring_init` and `cstring_delete` 
functions whenever you want to make a new instance of `cstring` and stop using it respectively,
in order not to cause any memory leaks, as there's no *constructor* and *destructor* to do it for you.  

The recommended way of initializing an empty string is by doing `cstring foo = cstring_init("")`.

## Functions

* `cstring_init`: Initiliazes string
* `cstring_delete`: Deallocates string
* `cstring_assign`: Assigns a new string to the current string
* `cstring_append`: Appends a string to the current string
* `cstring_insert`: Inserts a string at a specific index
* `cstring_push_back`: Adds a character at the end of the string
* `cstring_pop_back`: Removes the last character in the string
* `cstring_replace_char`: Replaces a character at a specific index
* `cstring_clear`: Erases the whole string
* `cstring_exists`: Checks to see if a (sub)string exists in the string
* `cstring_front`: Returns the first character of the string
* `cstring_back`: Returns the last character of the string
* `cstring_empty`: Checks if the string is empty
* `cstring_copy`: Makes a copy of a given `const char *`
* `cstring_resize`: Resizes the array stored inside the string `struct`
* `cstring_getline`: Reads a line from a stream
* `cstring_equal`: True if the strings are equal
* `cstring_not_equal`: True if the strings are not equal
* `cstring_greater`: True if the left hand string is greater than the right hand one
* `cstring_greater_or_equal`: True if the left hand string is greater than or equal to the right hand one
* `cstring_less`: True if the left hand string is less than the right hand one
* `cstring_less_or_equal`: True if the left hand string is less than or equal to the right hand one

## Example

See `test.c` for more.

```c
#include <stdio.h>
#include "cstring.h"

int
main(int argc, char **argv)
{
    cstring s = cstring_init("Foo");
    cstring_append(&s, "Bar.");
    printf("%s\n", s.str);
    cstring_delete(&s);

    return 0;
}
```
