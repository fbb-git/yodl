#include "ostream.ih"

void ostream_set_ws_level(register Ostream *out, unsigned value)
{
    out->d_ws_only = value;
}
