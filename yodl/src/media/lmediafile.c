#include "media.ih"

FILE *l_media_file(register Media *mp)
{
    return mp->d_file;
}
