#include "media.ih"

char const *media_filename(register Media *mp)
{
    return mp->d_filename;
}
