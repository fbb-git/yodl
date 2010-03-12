#include "string.ih"

static char s_buf[30];

char const *string_short(register char const *s)
{
    register char *cp;

    if (!s || !*s)
        return ("");

    strncpy(s_buf, s, 28);
    s_buf[29] = '\0';

    if (strlen(s_buf) > 25)
        strcpy(s_buf + 25, "...");

    while ((cp = strchr(s_buf, '\n')))
        *cp = ' ';

    return s_buf;
}
