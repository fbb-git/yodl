#include "ostream.ih"

void ostream_inserted_blanks(register Ostream *op)
{
    op->d_inserted_blanks = true;
}
