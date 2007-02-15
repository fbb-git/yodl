#include "message.ih"

void message(char const *fmt,...)
{
    va_list list;

    va_start (list, fmt);
    m_vmessage(fmt, list);
    va_end (list);

    if (m_message.d_last_show & (MSG_CRIT | MSG_ALERT | MSG_EMERG))
        exit(1);

    m_check_max_errors();
}
