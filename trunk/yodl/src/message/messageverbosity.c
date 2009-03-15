#include "message.ih"

static char s_buffer[10];

char const *message_verbosity()
{
    snprintf(s_buffer, 10, "%d", m_message.d_severity);
    return s_buffer;
}
