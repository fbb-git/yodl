#include "message.ih"

void message_setfilename(char const *fname)
{
    register char *cp;

    free(m_message.d_filename);

    m_message.d_filename = cp = new_str(!fname ? "" : fname);

    m_message.d_short_filename = (cp = strrchr(cp, '/')) ?
                                    cp + 1
                                :
                                    m_message.d_filename;
}
