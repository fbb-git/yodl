#include "message.ih"

int message_data = 0;

Message m_message;          /* set to 0 by the compiler */

char m_version[SIZEOF_VERSION];

char *m_severity[] =
    {
        "NONE",             /* these two must be here.                  */
        "ALL",              /* see `message_setverbosity'               */

        "DEBUG",            /* ordering must follow MESSAGE_SEVERITY    */
        "INFO",             /* from here                                */
        "NOTICE",
        "WARNING",
        "ERROR",
        "CRITICAL",
        "ALERT",
        "EMERGENCY",
    };
