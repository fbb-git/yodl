#include "parser.ih"

/*
    Read all tokens, store all blanks in temp. buffer, until all spaces and
    newlines are read. then, if there are more than one \n chars in the
    extracted info, call gram_PARAGRAPH to handle the extracted
    blanks. Otherwise, do a plain string insertion.
*/

bool p_handle_default_newline(register Parser *pp)
{
    bool multiple_newlines = false;
    LEXER_TOKEN token;
    char const *lastMatched;

    String str;
    String pushback;

    string_construct(&str, "\n");            /* at least one \n was read */
    string_construct(&pushback, 0);

    while (true)
    {
        token = lexer_lex(&pp->d_lexer);

        switch (token)
        {
            case TOKEN_SPACE:               /* collect all blanks       */
                string_addchar(&str, *p_matched(pp));
            continue;

            case TOKEN_NEWLINE:             /* and \n chars             */
                string_addchar(&str, '\n');
                multiple_newlines = true;
            continue;

            case TOKEN_EOR:                 /* ignore EOR               */
            continue;

            case TOKEN_SYMBOL:              /* make sure symbol and openpar */
                                            /* stay together                */
                string_addstr(&pushback, p_matched(pp));
                lexer_lex(&pp->d_lexer);    /* get the openpar itself       */
            /* FALLING THROUGH */

            default:                        /* keep what's there            */
                string_addstr(&pushback, lastMatched = p_matched(pp));
                                            /* keep +???? together          */
                if (strcmp(lastMatched, "+") == 0)
                    continue;

            /* FALLING THROUGH */

            case TOKEN_EOF:
                if (multiple_newlines)
                    p_paragraph(pp, &str);
                else
                    (*pp->d_insert)(pp, string_str(&str));
                
                lexer_push_str(&pp->d_lexer, string_str(&pushback));
                string_destroy(&pushback);
                string_destroy(&str);

                if (message_show(MSG_INFO))
                    message("P_HANDLE_DEFAULT_NEWLINE OUT");
            return token != TOKEN_EOF;
        }
    }
}
