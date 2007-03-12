#include "chartab.ih"

/*
    The regular expression of chartab-elements consists of the following
parts:

                "[[:space:]]*"          - start with optional whitespace
            "'((\\\\)?.)'"              - followed by one character between
                                            single quotes, optionally preceded
                                            by a backslash
                "[[:space:]]*"          - followed by optional white space
            "="                         - and an '=' sign
                "[[:space:]]*"          - followed by optional white space
            "\"(((\\\\.)|[^\"])*)\""    - followed by any series of chars,
                                          each optionally preceded by a \,
                                          enclosed in double string quotes

    d_regex_oct is identical to d_regex, but has the character expression
            "'\\\\([0-7]{3})'"          - three octal digits preceded by a \,
                                          surrounded by single quotes.
                                          Example: '\123'

    d_regex_hex is identical to d_regex, but has the character expression
            "'0x([0-9a-fA-F]{2})'"      - 0x followed by 2 hex digits,
                                          surrounded by single quotes.
                                          Example: '0xab'
*/

void chartab_construct() {
    if
    (
        regcomp
        (
            &chartab.d_regex,
                "[[:space:]]*"
            "'((\\\\)?.)'"
                "[[:space:]]*"
            "="
                "[[:space:]]*"
            "\"(((\\\\.)|[^\"])*)\""
            ,
            REG_EXTENDED | REG_NEWLINE
        )
        ||
        regcomp
        (
            &chartab.d_regex_oct,
                "[[:space:]]*"
            "'\\\\([0-7]{3})'"
                "[[:space:]]*"
            "="
                "[[:space:]]*"
            "\"(((\\\\.)|[^\"])*)\""
            ,
            REG_EXTENDED | REG_NEWLINE
        )
        ||
        regcomp
        (
            &chartab.d_regex_hex,
                "[[:space:]]*"
            "'0x([0-9a-fA-F]{2})'"
                "[[:space:]]*"
            "="
                "[[:space:]]*"
            "\"(((\\\\.)|[^\"])*)\""
            ,
            REG_EXTENDED | REG_NEWLINE
        )
    )
        if (message_show(MSG_EMERG))
            message("Chartab_construct(): regcomp() failed");

    stack_construct(&chartab.d_chartab_st, NULL);
}
