#include "args.ih"

void args_construct(int argc, char **argv,
                    char *options,
                    LongOption const *longOption)
{
    char *cp;
    size_t nopt;
    struct option *long_option;
    size_t nlong = 0;

    if (!longOption)
        long_option = new_calloc(1, sizeof(struct option));
    else
    {
        while (longOption[nlong++].d_name)
            ;

        long_option = new_memory(nlong, sizeof(struct option));

        for (nopt = 0; nopt < nlong; nopt++)
        {
            long_option[nopt].name      = longOption[nopt].d_name;
            long_option[nopt].has_arg   = longOption[nopt].d_type;
            long_option[nopt].flag      = 0;
            long_option[nopt].val       = longOption[nopt].d_value;
        }
    }

    memset(&args, 0, sizeof(Args));
    string_construct(&args.d_option, 0);

    args.d_argv = argv;
    args.d_argc = argc;

    if ((cp = getenv("home")) || (cp = getenv("HOME")))     /* set home */
        args.d_home = new_str(cp);

    args.d_programName = basename(argv[0]);         /*  set programname */
    args.d_initial_dir = new_getcwd();              /* set initial dir. */

    args.d_ok = true;
    nopt = 0;

    while (true)
    {
        int optchar = getopt_long(args.d_argc, args.d_argv,
                                  options, long_option, NULL);

        switch (optchar)
        {
            default:
                string_addchar(&args.d_option, optchar);
                new_size(&args.d_optarg, nopt + 1, nopt, sizeof(char *));
                args.d_optarg[nopt++] = optarg ? new_str(optarg) : 0;
            continue;                   /* at `while(true)' */

            case '?':
                args.d_ok = false;      /* stop processing at failure       */
            break;

            case EOF:
                args.d_optind = optind;
            break;
        }
        break;                          /* leave `while(true)'  */
    }
    free(long_option);
}
