#include "parser.ih"

char const *p_matched(register Parser *parser)
{
    return lexer_text(&parser->d_lexer);
}
