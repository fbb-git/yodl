#include "lexer.ih"

/*
    Subst      *d_subst_ptr     - external subst-structure
    Stack       d_empty_st      - empty
    size_t      d_empty_size    - 0
    bool        d_keep_ws       - false
    Stack       d_media_st      - empty
    void       *d_media_ptr     - NULL
    LEXER_TOKEN d_token         - TOKEN_UNKNOWN
    int         d_lastchar      - 0
    String      d_text          - empty string
*/

void lexer_construct(register Lexer *lp, Subst *sp)
{
    memset(lp, 0, sizeof(Lexer));
    string_construct(&lp->d_text, 0);
    lp->d_subst_ptr = sp;
    stack_construct(&lp->d_empty_st, NULL);     /* stores values    */
    stack_construct(&lp->d_media_st, media_destructor);
    lp->d_maxdepth = args_option('n') ? args_optint('n') : 
                                                    DEFAULT_MAX_NESTED_FILES;
    lp->d_maxreplacements = 
            10000 * 
            (args_option('r') ? args_optint('r') : DEFAULT_MAX_REPLACEMENTS);

    lp->d_chdirFun = args_option('L') ? l_noChdir : l_chdir;
}






