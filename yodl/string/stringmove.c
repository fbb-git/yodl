#include "string.ih"

String *string_move(char  *str)
{
    register String *sp = new_memory(1, sizeof(String));

    sp->d_length = strlen(str);
    sp->d_size = sp->d_length + 1;
    sp->d_str = str;

    return sp;
}
