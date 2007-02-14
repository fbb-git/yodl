#include "media.ih"

/*
    It's a file if the file ptr is != 0
*/

bool media_isFile(register Media *mp)
{
    return mp->d_isfile;
}
