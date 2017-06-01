#include "message.ih"

/*
    a decimal value: the corresponding MSG flags are set as the new
    verbosity level.

    one or more MSG_ values: these flags are set. Also, NONE and ALL
    may be used. The MSG_ prefix should be omitted, unique abbreviations may
    also be used (CR -> CRITICAL, D -> DEBUG)
*/

void message_setverbosity(int mode, char *arg)
{
    unsigned mask = MSG_NONE;

    if (sscanf(arg, "0x%x", (unsigned *)&mask) != 1)
    {
        char *tok = strtok(arg, " \t");

        while (tok)
        {
            size_t idx;
            for (idx = 0; idx < M_SIZEOF_M_SEVERITY; idx++)
            {
                if (strstr(m_severity[idx], tok) == m_severity[idx])
                {
                    if (idx == 0)           /* MSG_NONE         */
                        break;
                    if (idx == 1)           /* MSG_ALL          */
                        mask = (unsigned)MSG_ALL;
                    else
                        mask |= (1 << (idx - 2));   /* DEBUG: 1 << 0, etc. */
                    break;
                }
            }
            if (idx == M_SIZEOF_M_SEVERITY)
                if (message_show(MSG_WARNING))
                    message("Ignoring `%s' in verbosity setting", tok);

            tok = strtok(NULL, " \t");
        }
    }

    switch (mode)
    {
        case 0:
            m_message.d_severity = mask;
        break;

        case '+':
            m_message.d_severity |= mask;
        break;

        case '-':
            m_message.d_severity &= ~mask;
        break;

        default:
            if (message_show(MSG_ERR))
                message("VERBOSITY(%s)(...): 1st arg should be "
                            "empty, + or -", mode);
        break;
    }

    m_message.d_severity |= MSG_EMERG;
}
