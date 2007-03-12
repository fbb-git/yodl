#include "subst.ih"

void subst_insert(register Subst *sp, char const *fname,
                  char const *key, char const *value)
{
    char const *text;
    char *short_value = new_str(string_short(value));

    if ((text = s_state_insert(sp->d_start_state_ptr, key, value)) == 0)
    {
        if (message_show(MSG_NOTICE))
            message("%s(%s)(%s)", fname, key, short_value);
    }
    else if (message_show(MSG_ERR))
        message("%s(%s)(%s): Keeping existing definition `%s'",
                fname, key, short_value, string_short(text));

    free(short_value);
}
