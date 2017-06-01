#include "process.ih"

void process_destruct(Process *pp)
{
    free(pp->d_cmd);
    free(pp->d_input);
    free(pp->d_short_cmd);
    string_delete(&pp->d_output);
}
