#include "message.ih"

bool message_show(register MESSAGE_SEVERITY severity)
{
    m_message.d_last_show = severity;
    m_message.d_errors += (severity & MSG_ERR) != 0;

    return m_message.d_severity & severity;
}
