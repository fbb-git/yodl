#include "message.ih"

void message_setmaxerrors(size_t max)
{
    m_message.d_max_errors = max;
}
