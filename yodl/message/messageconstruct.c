#include "message.ih"

void message_construct(char const *argv0)
{
    char const *cp = strrchr(argv0, '/');

    if (cp)
        argv0 = cp + 1;

    m_message.d_program_name = new_str(argv0);

    m_message.d_severity =  MSG_ERR | MSG_EMERG | MSG_ALERT | MSG_CRIT;

    m_message.d_max_errors = 10;        /* make this configurable   */
    m_message.d_warn = true;
}
