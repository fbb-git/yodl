#include "line.ih"

bool Line::isEmpty() const
{
    return d_line.find_first_not_of(" \t") == string::npos;
}

