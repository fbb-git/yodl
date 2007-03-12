#include "media.ih"

bool media_fgetc(Media *mp)
{
    return mp->d_fgetc;
}
