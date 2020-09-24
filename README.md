# cstring

A simple and lightweight string library for C inspired by C++'s STL `string` class.

## Building

`cstring` is a static library. The header file is installed in `/usr/local/include` and
the library file in `/usr/local/lib`. In order to install it do the following

```shell
$ cd /path/to/cstring
$ make
$ sudo make install
$ make clean
```

If you want to uninstall the library do the following

```shell
$ cd /path/to/cstring
$ sudo make uninstall
```

In order to link `cstring` to your project use the `-lcstring` flag during the compilation.

## Usage

When using this library, you must to **always** call the `cstring_create` and `cstring_delete` 
functions whenever you want to make a new instance of `cstring` and stop using it respectively,
in order not to cause any memory leaks, as there's no *constructor* and *destructor* to do it for you.  

The recommended way of initializing an empty string is by doing `cstring foo = cstring_create("")`.

## Functions

* `cstring_create`: Initiliaze string
* `cstring_delete`: Deallocate string
* `cstring_assign`: Assign new string
* `cstring_append`: Append to end of string
* `cstring_prepend`: Prepend to beginning of string
* `cstring_insert`: Insert to a specific index
* `cstring_erase`: Erase portion of string
* `cstring_erase_matching`: Erase first match
* `cstring_erase_all_matching`: Erase all matches
* `cstring_trim`: Trim character
* `cstring_push_back`: Add character to end of string
* `cstring_pop_back`: Remove the last character from string
* `cstring_replace_char`: Replace character at a specific index
* `cstring_replace_str`: Replace portion of string
* `cstring_substr`: Extract a substring
* `cstring_swap`: Swap contents of two strings
* `cstring_shrink_to_fit`: Shrink string's capacity to fit its size
* `cstring_clear`: Clear contents of string
* `cstring_find`: Find index of first match (string)
* `cstring_find_first_of`: Find index of first match (character)
* `cstring_find_last_of`: Find index of last match (character)
* `cstring_front`: Get first character in string
* `cstring_back`: Get last character in string
* `cstring_empty`: Check if string is empty
* `cstring_starts_with_str`: Check if string starts with specified `char *`
* `cstring_ends_with_str`: Check if string ends with specified `char *`
* `cstring_starts_with_char`: Check if string starts with specified `char`
* `cstring_ends_with_char`: Check if string ends with specified `char`
* `cstring_copy`: Copy contents of a `char *`
* `cstring_resize`: Resize string
* `cstring_getline`: Read a line from a `FILE` stream
* `cstring_greater`: Check if `lhs` is greater than `rhs`
* `cstring_greater_or_equal`: True `lhs` is greater of equal to `rhs`
* `cstring_less`: Check if `lhs` is less than `rhs`
* `cstring_less_or_equal`: Check if `lhs` is less or equal to `rhs`

`lhs`: Left hand side  
`rhs`: Right hand side

## Example

See `test.c` for more.

```c
#include <stdio.h>
#include <cstring.h>

int
main(int argc, char **argv)
{
    cstring s = cstring_create("Foo");
    cstring_append(&s, "Bar.");
    printf("%s\n", s.str);
    cstring_delete(&s);

    return 0;
}
```
