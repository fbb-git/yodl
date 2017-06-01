#include "process.ih"

void process_construct(Process *pp, char const *fname, char *cmd, char *input)
{
    pp->d_fname     = fname;

    pp->d_cmd       = cmd;
    pp->d_short_cmd = new_str(string_short(cmd));

    pp->d_input     = input;

    pp->d_output    = string_new(0);

}
