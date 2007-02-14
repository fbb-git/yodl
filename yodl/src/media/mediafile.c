#include "media.ih"

FILE *m_file(register Media *mp)
{
    return mp->d_file;
}
