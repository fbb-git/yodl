#include "out.ih"

void Out::numberedLine(std::string const &line)
{
    cout << d_indent << setw(2) << ++d_number << ": " << line << '\n';
}
