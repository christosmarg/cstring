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

In order to link `cstring` to your project use the `-lcstring` flag during compilation.

## Usage

When using this library, you must to **always** call the `cstring_create` and `cstring_delete` 
functions whenever you want to make a new instance of `cstring` and stop using it respectively,
in order not to cause any memory leaks, as there's no *constructor* and *destructor* to do it for you.  

The recommended way of initializing an empty string is by doing `cstring foo = cstring_create(CSTRING_INIT_EMPTY)`.

## Functions

* `cstring_create`: Initiliaze string.
* `cstring_delete`: Deallocate string.
* `cstring_assign`: Assign new string.
* `cstring_insert`: Insert at a specific index.
* `cstring_append`: Append to end of string.
* `cstring_prepend`: Prepend to beginning of string.
* `cstring_erase`: Erase portion of string.
* `cstring_erase_matching`: Erase first match.
* `cstring_erase_all_matching`: Erase all matches.
* `cstring_trim`: Trim character.
* `cstring_push_back`: Add character to end of string.
* `cstring_pop_back`: Remove the last character from string.
* `cstring_replace_char`: Replace character at a specific index.
* `cstring_replace_str`: Replace portion of string.
* `cstring_substr`: Extract a substring.
* `cstring_swap`: Swap contents of two strings.
* `cstring_sort`: Sort an array of `cstring` objects.
* `cstring_sort_partial`: Like `cstring_sort` but for part of the array.
* `cstring_sort_chars`: Sort `cstring`'s contents.
* `cstring_sort_chars_partial`: Like `cstring_sort_chars` but for part of the string.
* `cstring_shrink_to_fit`: Shrink string's capacity to fit its size.
* `cstring_clear`: Clear contents of string
* `cstring_find`: Find first occurence of a pattern in string.
* `cstring_rfind`: Fnid last occurence of a pattern in string.
* `cstring_find_first_of`: Find first occurence of specified characters in string.
* `cstring_find_first_not_of`: Find the first character that does not match any of the specified characters.
* `cstring_find_last_of`: Find last occurence of specified characters in string.
* `cstring_find_last_not_of`: Find the last character that does not match any of the specified characters.
* `cstring_front`: Get first character in string.
* `cstring_back`: Get last character in string.
* `cstring_empty`: Check if string is empty.
* `cstring_starts_with_str`: Check if string starts with specified `char *`.
* `cstring_ends_with_str`: Check if string ends with specified `char *`.
* `cstring_starts_with_char`: Check if string starts with specified `char`.
* `cstring_ends_with_char`: Check if string ends with specified `char`.
* `cstring_data`: Get string's content in raw bytes.
* `cstring_copy`: Copy contents of a `char *`.
* `cstring_resize`: Resize string.
* `cstring_getline`: Read a line from a `FILE` stream.
* `cstring_equal`: Check if `lhs == rhs`.
* `cstring_greater`: Check if `lhs > rhs`.
* `cstring_greater_or_equal`: Check if `lhs >= rhs`.
* `cstring_less`: Check if `lhs < rhs`.
* `cstring_less_or_equal`: Check if `lhs <= rhs`.

`lhs`: Left hand side  
`rhs`: Right hand side

## Macros

* `CSTRING_OUT_OF_BOUNDS`: Check if `pos` is out of bounds.
* `CSTRING_ARR_LEN`: Determine an array's length. The macro must be called in the same function the array is declared.
* `CSTRING_FLAG_CHECK`: Check if flag is on.
* `CSTRING_MALLOC`: Allocate memory with error checking.
The following macros can only be used in debug mode
* `CSTIRNG_DBG_LOG`: Prints a message in the format of `DEBUG: file:line:func(): msg`.
* `CSTRING_DBG_LOG_CSTR_INFO`: Prints all the contents of a `cstring` struct. The argument *has* to be a pointer.
* `CSTRING_DBG_LOG_CSTR_INFO_NPTR`: Like `CSTRING_DBG_LOG_CSTR_INFO` but the argument has to be a non-pointer.
* `CSTRING_DBG_LOG_STR_INFO`: Print contents of a normal string.

## Constants

* `CSTRING_NPOS`: Signifies that a pattern hasn't been found inside the string. Its value is -1.
* `CSTRING_INIT_EMPTY`: Used with `cstring_create` in case the string is to be initiliazed as empty.

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
