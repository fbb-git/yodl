#include "parser.ih"

char const *p_matched(register Parser *parserPtr)
{
    return lexer_text(&parserPtr->d_lexer);
}
