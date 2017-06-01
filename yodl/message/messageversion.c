#include "message.ih"

char const *message_version()
{
    snprintf(m_version, SIZEOF_VERSION, "%s version %s\n",
                        m_message.d_program_name, VERSION);

    return m_version;
}
