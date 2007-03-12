#include "media.ih"

long m_set_offset(register Media *mp)
{
    return mp->d_offset = ftell(m_file(mp));
}
