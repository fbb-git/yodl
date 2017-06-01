#include "lexer.ih"

void lexer_push_file(register Lexer *lp, char const *pathname)
{
    l_push(lp, pathname, l_media_construct_file);
    (*lp->d_chdirFun)(lp, pathname);    
}
