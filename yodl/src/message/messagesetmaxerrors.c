#include "message.ih"

void message_setmaxerrors(unsigned max)
{
    m_message.d_max_errors = max;
}
