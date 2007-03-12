#include "message.ih"

void message_setseverity(MESSAGE_SEVERITY severity)
{
    m_message.d_severity = severity | MSG_EMERG;
}
