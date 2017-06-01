#include "message.ih"

void m_vmessage (char const *format, va_list args)
{
    if (m_message.d_filename && m_message.d_lineno)
    {
        if (m_message.d_severity & MSG_DEBUG)
            fprintf(stderr, "%s:%u:\n\t", m_message.d_filename,
                                          (unsigned)m_message.d_lineno);
        else
            fprintf(stderr, "%s:%u: ", m_message.d_short_filename,
                                       (unsigned)m_message.d_lineno);
    }
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
}
