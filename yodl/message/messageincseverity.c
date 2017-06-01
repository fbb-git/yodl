#include "message.ih"

static int s_mask = MSG_EMERG;

void message_incseverity()
{
    s_mask = (s_mask >> 1) | MSG_EMERG;
    m_message.d_severity |= s_mask;
}
