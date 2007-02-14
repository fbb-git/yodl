#include "media.ih"

long l_media_set_offset(register Media *mp)
{
    return mp->d_offset = ftell(l_media_file(mp));
}
