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

* `cstring cstring_create(const char *s)`: Initiliaze string
* `void cstring_delete(cstring *cs)`: Deallocate string
* `void cstring_assign(cstring *cs, const char *s)`: Assign new string
* `void cstring_append(cstring *cs, const char *s)`: Append to end of string
* `void cstring_prepend(cstring *cs, const char *s)`: Prepend to beginning of string
* `void cstring_insert(cstring *cs, const char *s, size_t i)`: Insert to a specific index
* `void cstring_erase(cstring *cs, size_t pos, size_t len)`: Erase portion of string
* `void cstring_erase_matching(cstring *cs, const char *s)`: Erase first match
* `void cstring_erase_all_matching(cstring *cs, const char *s)`: Erase all matches
* `void cstring_trim(cstring *cs, char c)`: Trim character
* `void cstring_push_back(cstring *cs, char c)`: Add character to end of string
* `void cstring_pop_back(cstring *cs)`: Remove the last character from string
* `void cstring_replace_char(cstring *cs, size_t i, char c)`: Replace character at a specific index
* `void cstring_replace_str(cstring *cs, const char *s, size_t pos, size_t len)`: Replace portion of string
* `cstring cstring_substr(const cstring *cs, size_t pos, size_t len)`: Extract a substring
* `void cstring_swap(cstring *lhs, cstring *rhs)`: Swap contents of two strings
* `void cstring_shrink_to_fit(cstring *cs)`: Shrink string's capacity to fit its size
* `void cstring_clear(cstring *cs)`: Clear contents of string
* `size_t cstring_find(const cstring *cs, const char *s)`: Find index of first match (string)
* `size_t cstring_find_first_of(const cstring *cs, char c)`: Find index of first match (character)
* `size_t cstring_find_last_of(const cstring *cs, char c)`: Find index of last match (character)
* `char cstring_front(const cstring *cs)`: Get first character in string
* `char cstring_back(const cstring *cs)`: Get last character in string
* `int cstring_empty(const cstring *cs)`: Check if string is empty
* `int cstring_starts_with_str(const cstring *cs, const char *s)`: Check if string starts with `s`
* `int cstring_ends_with_str(const cstring *cs, const char *s)`: Check if string ends with `s`
* `int cstring_starts_with_char(const cstring *cs, char c)`: Check if string starts with `c`
* `int cstring_ends_with_char(const cstring *cs, char c)`: Check if string ends with `c`
* `char *cstring_copy(const char *cs)`: Copy contents of `s`
* `void cstring_resize(cstring *cs, size_t newcapacity)`: Resize string
* `cstring *cstring_getline(FILE *fd, cstring *cs, char delim)`: Read a line from a `FILE` stream
* `int cstring_equal(const cstring *lhs, const cstring *rhs)`: Check if strings are equal
* `int cstring_not_equal(const cstring *lhs, const cstring *rhs)`: Check if strings are not equal
* `int cstring_greater(const cstring *lhs, const cstring *rhs)`: Check if `lhs` is greater than `rhs`
* `int cstring_greater_or_equal(const cstring *lhs, const cstring *rhs)`: True `lhs` is greater of equal to `rhs`
* `int cstring_less(const cstring *lhs, const cstring *rhs)`: Check if `lhs` is less than `rhs`
* `int cstring_less_or_equal(const cstring *lhs, const cstring *rhs)`: Check if `lhs` is less or equal to `rhs`

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
