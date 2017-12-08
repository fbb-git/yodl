#include "line.ih"

Line::Type Line::next()
{
    if (not getline(*d_input, d_line))
        return d_type = ENDFILE;

    if (isEmpty())
        return d_type = EMPTY;

    if (markerPattern())
        return d_type;

    return d_type = TEXT;
}
