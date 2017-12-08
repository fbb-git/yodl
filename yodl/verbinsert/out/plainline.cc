#include "out.ih"

void Out::plainLine(std::string const &line)
{
    cout << d_indent << line << '\n';
}
