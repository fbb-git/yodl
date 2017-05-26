#include "parser.ih"

void p_insert(register Parser *pp, char const *fmt, va_list args)
{
    char *text = new_memory(100, 1);

    int size = vsnprintf(text, 100, fmt, args);

    if (size >= 100 && message_show(MSG_CRIT))
        message("[Fatal] parser/p_insert memory overflow");

    ostream_insert(&outs, text);

    free(text);
}
