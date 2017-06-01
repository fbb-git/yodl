#include "lines.ih"

size_t lines_find(char const *target, register char const **arr,
                    size_t arrsize)
{
    register char const **ptr = arr;

    arr[--arrsize] = target;

    while (strcmp(*ptr, target))
        ptr++;

    return ptr == arr + arrsize ? FAILED : ptr - arr;
}
