#include "message.ih"

/*
    a, c, e, d, i, n, w, are used to set corresponding flags. Emerg is
    always set
*/

static char s_flags[] = "dinweca";

void message_optarg(register char const *cp)
{
    size_t mask = MSG_EMERG;
    register char const *ret;

    while (*cp && (ret = strchr(s_flags, tolower(*cp))))
    {
        mask |= (1 << (ret - s_flags));
        cp++;
    }

    if (*cp)
        if (message_show(MSG_ERR))
            message("Flag -m `%c' not supported. Valid are `dinweca'", *cp);

    m_message.d_severity |= mask;
}
