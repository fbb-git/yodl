#include "string.ih"

static char s_buf[2];

void string_addchar(register String *sp, int c)
{
    s_buf[0] = c;
    s_buf[1] = 0;

    string_addstr(sp, s_buf);
}
