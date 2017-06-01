#include "message.ih"

void m_check_max_errors()
{
    if (m_message.d_errors >= m_message.d_max_errors)
    {
        fprintf(stderr, "Terminating after %u errors\n", 
                        (unsigned)m_message.d_max_errors);
        exit(1);
    }
}
