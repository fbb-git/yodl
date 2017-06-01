#include "string.ih"

/*
    string_format() assumes C99 is active (see the snprintf() manpage)
*/

void string_format(String *s, char const *fmt, ...)
{
    va_list list;
    va_start(list, fmt);

    free(s->d_str);
    s->d_str = string_vformat(&s->d_size, fmt, list);
    s->d_length = s->d_size - 1;

    va_end(list);
}
