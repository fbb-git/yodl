#include "out.ih"

void Out::insert(std::string const &line)
{
    ++d_nLines;
    return (this->*d_insert)(line);
}
