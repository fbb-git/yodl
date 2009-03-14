#include "chartab.ih"

/*
    See also chatab_construct() for the description of d_regex_hex and
    d_regex_oct.

    character tables consist of lines, each line containing a 'x' = "redef"
    phrase.

    The problem here is, of course, that we MUST have the newlines. So, we
    MUST make sure that the WS level, not using -k, doesn't kill our newlines.
    This is realized by yodl/gramdefinechartable.c by calling
    parser_push_ws_level() and parser_pop_ws_level().

    One match is described by:

    match:  1              23            (count match by parenthesis number)

        \s*'(\\?.)'\s*=\s*"(((\\.)|[^"])*)"
             1111            22222 3333
           55555555         4444444444444

    \s: [[:space:]]

    1:  maybe backslash, then any char within stringquotes
    2:  backslash, then any char
    3:  no double quote
    4:  (2) or (3), as often as required


    The 'x' part may contain escape sequences: '(\.|)' or '\.'
    The "redef" part may contain escape sequences "([^"]|\.)*"
*/

typedef enum
{
    REGEX_HEX,
    REGEX_PLAIN,
    REGEX_OCT
}
REGEX_TYPE;

static regmatch_t pmatch[5];

void ct_parse_table(char **table, register char *arg)
{
    int idx;
    size_t key = 0;     /* to prevent `may be used initialized' warning */
                        /* produced by some compilers                   */    

    while (*arg)                                    /* Process `arg'    */
    {
        REGEX_TYPE regex_type;
        unsigned uns_key;
        register char *chartext;

            /* Match the next element in `arg'  */

                                    /* 5: max 5 subexpressions, 0: no flags */
        if (!regexec(&chartab.d_regex, arg, 5, pmatch, 0))
            regex_type = REGEX_PLAIN;
        else if (!regexec(&chartab.d_regex_oct, arg, 5, pmatch, 0))
            regex_type = REGEX_OCT;
        else if (!regexec(&chartab.d_regex_hex, arg, 5, pmatch, 0))
            regex_type = REGEX_HEX;
        else
        {
            if (message_show(MSG_ERR))
                message("DEFINECHARTABLE: Entry `%s' not recognized",
                                                    string_short(arg));

            if (!(arg = strchr(arg, '\n')))     /* find next definition     */
                return;

            arg++;                              /* skip \n                  */
            continue;                           /* retry at the next one    */
        }


            /* Got a match. Terminate the matched elements  */

        arg[pmatch[1].rm_eo] = 0;               /* terminate matched char   */
        arg[pmatch[3].rm_eo] = 0;               /* terminate matched string */
        chartext = arg + pmatch[1].rm_so;


            /* Convert the matched character text to a char (key) value */

        switch (regex_type)
        {
            case REGEX_HEX:
                sscanf(chartext, "%x", &uns_key);
                key = uns_key;
            break;

            case REGEX_OCT:
                sscanf(chartext, "%o", &uns_key);
                key = uns_key;
                if (key > 0xff)
                {
                    if (message_show(MSG_ERR))
                        message("DEFINECHARTABLE: Character value `\\%s' "
                            "exceeds 0%o (255)", chartext, 255);

                    arg += pmatch[0].rm_eo + 1;

                    continue;                   /* retry at the next one    */
                }
            break;

            case REGEX_PLAIN:
            {
                size_t dummy = 0;               /* not used by ct_ascii */
                key = ct_ascii(chartext, &dummy);
            }
            break;
        }

        if (message_show(MSG_INFO))
            message("chartab[%s] = `%s'", chartext, arg + pmatch[3].rm_so);

        free(table[key]);
        table[key] = ct_string(arg + pmatch[3].rm_so);
        arg += pmatch[0].rm_eo + 1;
    }

    idx = strspn(arg, " \t\n");
    if (arg[idx])
        if (message_show(MSG_ERR))
            message("DEFINECHARTABLE: Illegal table contents `%s'",
                                                    string_short(arg + idx));
}
