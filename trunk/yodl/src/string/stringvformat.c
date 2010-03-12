#include "string.ih"

/*
    string_vformat() assumes C99 is active (see the snprintf() manpage)
*/

char *string_vformat(size_t *nret, char const *fmt, va_list list)
{
    size_t n;
    register char *cp;
    va_list copy;

    va_copy(copy, list);
    n = 1 + vsnprintf(0, 0, fmt, list);
    vsnprintf(cp = new_memory(n, sizeof(char)), n, fmt, copy);
    va_end(copy);

    *nret = n;
    return cp;
}
