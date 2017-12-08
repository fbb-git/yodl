#include "process.ih"

void Process::setTarget(char const *target)
{
    d_line.setTarget(target);

    d_run = &Process::processTarget;
}
