#include "message.ih"

void error_setprogname(char const *name)
{
    char const *cp = strrchr(name, '/');

    if (cp)
        name = cp + 1;

    free (m_message.d_program_name);
    m_message.d_program_name = new_str(name);
}
