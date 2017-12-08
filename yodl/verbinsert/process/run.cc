#include "process.ih"

void Process::run()
{
    if (d_run == 0)
        throw string{ "No run-option selected" };

    (this->*d_run)();
}
