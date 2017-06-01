#include "message.ih"

void message_error(char const *fmt,...)
{
    va_list list;

    message_show(MSG_ERR);

    va_start (list, fmt);
    m_vmessage(fmt, list);
    va_end (list);

    m_check_max_errors();
}
