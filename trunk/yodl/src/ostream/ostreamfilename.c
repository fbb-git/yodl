#include "ostream.ih"

char const *ostream_filename(register Ostream *out)
{
    return out->d_filename;
}
