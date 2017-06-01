#include "message.ih"

void warning(char const *fmt,...)
{
    va_list list;

    va_start(list, fmt);
    m_vmessage(fmt, list);
    va_end(list);
}
