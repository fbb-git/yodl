#include "message.ih"

void message_error(char const *fmt,...)
{
    va_list list;

    message_show(MSG_ERR);

    va_start (list, fmt);
    m_vmessage(fmt, list);
    va_end (list);

    if (m_message.d_errors >= m_message.d_max_errors)
    {
        fprintf(stderr,
                "Terminating after %u errors\n", m_message.d_max_errors);
        exit(1);
    }
}
