#include "process.ih"

void process_destroy(Process *pp)
{
    free(pp->d_cmd);
    free(pp->d_input);
    free(pp->d_short_cmd);
    string_destructor(pp->d_output);
}
