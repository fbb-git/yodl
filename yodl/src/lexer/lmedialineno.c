#include "lexer.ih"

unsigned l_media_lineno(register Media *mp)
{
    return mp->d_lineno;
}
