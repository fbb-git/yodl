#include "string.ih"

/*
    string_vformat() assumes C99 is active (see the snprintf() manpage)
*/

char *string_vformat(unsigned *nret, char const *fmt, va_list list)
{
    int n;
    register char *cp;

    n = 1 + vsnprintf(0, 0, fmt, list);
    vsnprintf(cp = new_memory(n, sizeof(char)), n, fmt, list);

    *nret = n;
    return cp;
}
