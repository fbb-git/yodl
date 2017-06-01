#include "parser.ih"

/*
    By default, all tokens are inserted, except for UNKNOWN, EOR and EOF,
    which by default result in Yodl's premature termination, except for EOR,
    which continues at no further action.

    The COLLECT_SET 
        - collects all input, without any interpretation
        - ignores the surrounding ()s

    The DEFAULT_SET
        - terminates normally at EOF
        - handles symbols as macros or as plain symbols
        - handles newlines by (maybe) paragraphs
        - handles + chars by the + handler
        - inserts all other tokens

    The IGNORE_SET ignores everything, including the () surrounding
    a parameter

    The NOTRANS_SET 
        - inserts all input, without any interpretation, using the currently
            active inserter function
        - handles CHAR() but no other symbols
        - ignores the surrounding ()s

    The NOEXPAND_SET 
        - handles CHAR() but no other symbols
        - ignores the surrounding ()s
        - handles + chars by a + handler
        - prematurely ends Yodl at EOF
        - inserts other tokens

    The SKIPWS_SET
        - ignores all blanks
        - ends at the first non-ws token, which is pushd back
        - prematurely ends Yodl at EOF
*/

void p_setupHandlerSet()
{
    register size_t set;
    register size_t token;

/*
    By default, all tokens are inserted, except for UNKNOWN, EOR and EOF,
    which by default result in Yodl's premature termination, except for EOR,
    which continues at no further action.
*/
    for (set = 0; set < SIZEOF_HANDLER_SET_ELEMENTS; set++)
    {
        for (token = 0; token < SIZEOF_TOKEN; token++)
            ps_handlerSet[set][token] = p_handle_insert;

        ps_handlerSet[set][TOKEN_UNKNOWN]   = p_handle_unknown;
        ps_handlerSet[set][TOKEN_EOF]       = p_handle_unexpected_eof;
        ps_handlerSet[set][TOKEN_EOR]       = p_handle_ignore;
    }

/*
    The COLLECT_SET 
        - collects all input, without any interpretation
        - ignores the surrounding ()s
*/
    ps_handlerSet[COLLECT_SET][TOKEN_CLOSEPAR]  = p_handle_parlist_closepar;
    ps_handlerSet[COLLECT_SET][TOKEN_OPENPAR]   = p_handle_parlist_openpar;

/*
    The DEFAULT_SET
        - terminates normally at EOF
        - handles symbols as macros or as plain symbols
        - handles newlines by (maybe) paragraphs
        - handles + chars by the + handler
        - inserts all other tokens
*/
    ps_handlerSet[DEFAULT_SET][TOKEN_EOF]       = p_handle_default_eof;
    ps_handlerSet[DEFAULT_SET][TOKEN_NEWLINE]   = p_handle_default_newline;
    ps_handlerSet[DEFAULT_SET][TOKEN_PLUS]      = p_handle_default_plus;
    ps_handlerSet[DEFAULT_SET][TOKEN_SYMBOL]    = p_handle_default_symbol;

/*
    The IGNORE_SET ignores everything, including the () surrounding
    a parameter, EOF prematurely ends Yodl, EOR continues parsing.
*/
    for (token = 0; token < SIZEOF_TOKEN; token++)
        ps_handlerSet[IGNORE_SET][token] = p_handle_ignore;

    ps_handlerSet[IGNORE_SET][TOKEN_EOF]        = p_handle_unexpected_eof;
    ps_handlerSet[IGNORE_SET][TOKEN_CLOSEPAR]   = p_handle_ignore_closepar;
    ps_handlerSet[IGNORE_SET][TOKEN_OPENPAR]    = p_handle_ignore_openpar;
    ps_handlerSet[IGNORE_SET][TOKEN_UNKNOWN]    = p_handle_unknown;

/*
    The NOEXPAND_SET 
        - handles CHAR() but no other symbols
        - ignores the surrounding ()s
        - handles + chars by a + handler
        - prematurely ends Yodl at EOF
        - inserts other tokens
*/
    ps_handlerSet[NOEXPAND_SET][TOKEN_CLOSEPAR] = p_handle_parlist_closepar;
    ps_handlerSet[NOEXPAND_SET][TOKEN_OPENPAR]  = p_handle_parlist_openpar;
    ps_handlerSet[NOEXPAND_SET][TOKEN_PLUS]     = p_handle_noexpand_plus;
    ps_handlerSet[NOEXPAND_SET][TOKEN_SYMBOL]   = p_handle_noexpand_symbol;

/*
    The NOTRANS_SET 
        - inserts all input, without any interpretation, using the currently
            active inserter function
        - handles CHAR() but no other symbols
        - ignores the surrounding ()s

    It's identical to NOEXPAND_SET, but when used, the character table has
    been suppressed by p_begin_nested()
*/
    ps_handlerSet[NOTRANS_SET][TOKEN_CLOSEPAR]  = p_handle_parlist_closepar;
    ps_handlerSet[NOTRANS_SET][TOKEN_OPENPAR]   = p_handle_parlist_openpar;
    ps_handlerSet[NOTRANS_SET][TOKEN_PLUS]      = p_handle_noexpand_plus;
    ps_handlerSet[NOTRANS_SET][TOKEN_SYMBOL]    = p_handle_noexpand_symbol;

/*
    The SKIPWS_SET
        - ignores all blanks
        - ends at the first non-ws token, which is pushd back
        - prematurely ends Yodl at EOF
*/
    for (token = 0; token < SIZEOF_TOKEN; token++)
        ps_handlerSet[SKIPWS_SET][token] = p_handle_skipws_unget;

    ps_handlerSet[SKIPWS_SET][TOKEN_EOF]        = p_handle_unexpected_eof;
    ps_handlerSet[SKIPWS_SET][TOKEN_EOR]        = p_handle_ignore;
    ps_handlerSet[SKIPWS_SET][TOKEN_UNKNOWN]    = p_handle_unknown;
    ps_handlerSet[SKIPWS_SET][TOKEN_SPACE]      = p_handle_ignore;
    ps_handlerSet[SKIPWS_SET][TOKEN_NEWLINE]    = p_handle_ignore;

}
