#include "yodl.h"

static LongOption long_options[] =
{
    { "define",                 required_argument,  'D' },
    { "definemacro",            required_argument,  'd' },
    { "help",                   no_argument,        'h' },
    { "include",                required_argument,  'I' },
    { "index",                  required_argument,  'i' },
    { "keep-ws",                no_argument,        'k' },
    { "legacy-include",         no_argument,        'L' },
    { "live-data",              required_argument,  'l' },
    { "messages",               required_argument,  'm' },
    { "max-nested-files",       required_argument,  'n' },
    { "output",                 required_argument,  'o' },
    { "preload",                required_argument,  'p' },
    { "max-replacements",       required_argument,  'r' },
    { "trace",                  no_argument,        't' },
    { "version",                no_argument,        'V' },
    { "verbose",                no_argument,        'v' },
    { "warranty",               no_argument,        'W' },
    { "warn",                   no_argument,        'w' },

    { 0,                        0,                  0   }
};

void  preamble(int argc, char **argv)       /* global initializations       */
{
    message_construct(argv[0]);             /* setup the message struct     */
    hashmap_construct(&symtab);             /* initialize the symbol table  */

    builtin_insert(&symtab, builtin_array); /* insert builtins into  symtab */

    args_construct(argc, argv, "?D:d:hi:I:kl:Lm:n:o:p:r:tVvWw", long_options);

    if (args_options("VW"))
    {
        printf("%s\n", message_version());
        if (args_option('W'))
            warranty();
        exit(1);
    }

    if (!args_ok() || !args_nArgs())
        usage();

    set_message_level();

    add_user_symbols();
    add_user_macros();

    insert_XXincludePath();

    if (message_errors())
        if (message_show(MSG_CRIT))
            message("Error(s) in command line arguments. Terminating");

                                            /* prepare the output stream    */
    ostream_construct(&outs, args_option('t'), args_optarg('o'));

    chartab_construct();                    /* prepare chartab construction */
    parser_construct(&parser, &symtab,      /* initialize the parser        */
                              &outs);
}
