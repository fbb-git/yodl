#include "process.ih"

String const *process_output(Process *pp)
{
    return pp->d_output;
}
