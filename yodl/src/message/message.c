#include "message.ih"

void message(char const *fmt,...)
{
    va_list list;

    va_start (list, fmt);
    m_vmessage(fmt, list);
    va_end (list);

    if (m_message.d_last_show & (MSG_CRIT | MSG_ALERT | MSG_EMERG))
        exit(1);

    if (m_message.d_errors >= m_message.d_max_errors)
    {
        fprintf(stderr,
                "Terminating after %u errors\n", m_message.d_max_errors);
        exit(1);
    }
}
