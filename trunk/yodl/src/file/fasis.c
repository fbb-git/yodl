#include "file.ih"

char *f_as_is(char const *request, String *fname)
{
    char *str;

    if (f_opt_extension(fname) == SUCCESS)
    {
        str = new_str(string_str(fname));
        if (message_show(MSG_INFO))
            message("`%s' is read as `%s'", request, str);
    }
    else
    {
        str = NULL;
        if (message_show(MSG_NOTICE))
            message("`./%s[%s] is not readable", request, DEFAULT_EXT);
    }

    string_destroy(fname);
    return str;
}
