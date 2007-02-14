#include "yodl.h"

int main (int argc, char **argv)
{
    args_data = chartab_data = parser_data = message_data;

    preamble(argc, argv);   /* global initializations, set up signal handlers
                                and initial data. We need these to operate
                                properly before doing anything else
                            */
    if (message_show(MSG_NOTICE))
        message("Current Working Directory: `%s'", args_initial_dir());

    parser_process(&parser);

    return message_errors();            /* all done */
}

/* For SYSTEMs that need strerror(): */
#ifdef NEEDSTRERROR
char *
strerror (int nr)
{
  extern char
   *sys_errlist[];
  extern int
    sys_nerr;

  if (nr < 0 || nr >= sys_nerr)
    return ("Unknown error.");
  return (sys_errlist[nr]);
}
#endif
