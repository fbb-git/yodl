#include "lexer.ih"

char const  *lexer_filename(register Lexer *lp)
{
    char const *filename;
    register Media *mp = lp->d_media_ptr;

    if (!mp)
        return "<none>";

    filename = l_media_filename(mp);
    return !strcmp(filename, "-") ? "stdin" : filename;
}
