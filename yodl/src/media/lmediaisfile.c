#include "media.ih"

/*
    It's a file if the file ptr is != 0
*/

bool l_media_isFile(register Media *mp)
{
    return mp->d_isfile;
}
