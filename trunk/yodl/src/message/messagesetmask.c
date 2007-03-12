#include "message.ih"

/*
    a decimal value: the corresponding MSG flags are set as the new
    verbosity level.
*/

void message_setmask(size_t mask)
{
    m_message.d_severity = mask | MSG_ALERT;    /* new verbosity setting    */
}
