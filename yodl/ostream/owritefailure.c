#include "ostream.ih"

void o_write_failure()
{
    if (message_show(MSG_ALERT))
        message("Write failure: `%s'", strerror(errno));
}
