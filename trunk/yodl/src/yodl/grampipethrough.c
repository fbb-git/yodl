#include "yodl.h"

void gram_PIPETHROUGH()
{
    char *cmd;
    char *short_cmd;
    char *input;

    parser_push_fun("PIPETHROUGH");

    cmd = parser_parlist(&parser, COLLECT_SET);
    short_cmd = new_str(string_short(cmd));

    parser_skipws(&parser);
    input = parser_parlist(&parser, COLLECT_SET);
    if (message_show(MSG_NOTICE))
        message("PIPETHROUGH echo '%s' | %s", string_short(input), short_cmd);
    free(short_cmd);

    if (!check_live_data(cmd))
    {
        free(input);
        free(cmd);
    }
    else
    {
        Process process;
        String const *output;

        process_construct (&process, "PIPETHROUGH", cmd, input);
        process_fork(&process);
        output = process_output(&process);

        lexer_push_str(&parser.d_lexer, string_str(output));

        process_destroy(&process);
    }
    parser_pop_fun();
}
