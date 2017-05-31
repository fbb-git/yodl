#include "parser.ih"

void parser_insertSubst(register Parser *pp, int index)
{
    StrVectorPair const *ptr = strVector_index(
                                    subst_strVector(&pp->d_subst),
                                    index);

    lexer_push_str(&pp->d_lexer, pp->d_useSubst ? ptr->d_value : ptr->d_key);
}
