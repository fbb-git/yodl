#include "ostream.ih"

long ostream_offset(register Ostream *ostream)
{
    return ftell(ostream->d_stream);
}
