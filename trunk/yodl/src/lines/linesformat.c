#include "lines.ih"

void lines_format(Lines *lines, char const *fmt, ...)
{
    va_list list;
    size_t n;

    va_start(list, fmt);
    lines_grab(lines, string_vformat(&n, fmt, list));
    va_end(list);
}
