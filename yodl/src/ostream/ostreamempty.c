#include "ostream.ih"

bool ostream_empty(register Ostream *os)
{
    return os->d_empty;
}
