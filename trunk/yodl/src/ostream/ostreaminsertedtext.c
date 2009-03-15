#include "ostream.ih"

bool ostream_inserted_text(register Ostream *op)
{
    return !op->d_inserted_blanks;
}
