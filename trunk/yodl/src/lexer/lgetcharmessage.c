#include "lexer.ih"

static char s_printChar[] = " (.)";

void l_getchar_message(register Lexer *lp, char const *preamble, int ch)
{
    s_printChar[2] = ch;

    if (message_show(MSG_DEBUG))
        message("%s char 0x%x%s", preamble,
                                ch, isprint(ch) ? s_printChar : "");
}
