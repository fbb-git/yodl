#include "lexer.ih"

bool l_media_fgetc(Media *mp)
{
    return mp->d_fgetc;
}
