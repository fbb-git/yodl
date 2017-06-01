#include "string.ih"

static bool     s_initialized;
static regex_t  s_strip;
static regmatch_t pmatch[2];

char *string_strip(char **str)
{
    if (!s_initialized)
    {
        s_initialized = true;
        if
        (
            regcomp
            (
                &s_strip,
                    "^[[:space:]]*"
                "("
                    "([^[:space:]].*[^[:space:]])"
                    "|"
                    "[^[:space:]]*"
                ")"
                    "[[:space:]]*$"
                ,
                REG_EXTENDED | REG_NEWLINE
            )
        )
        {
            message_show(MSG_EMERG);
            message("string_strip() regcomp() failed");
        }
    }

    if (regexec(&s_strip, *str, 2, pmatch, 0))      /* no match */
        **str = 0;
    else
    {
        (*str)[pmatch[1].rm_eo] = 0;
        *str += pmatch[1].rm_so;
    }

    return *str;
}
