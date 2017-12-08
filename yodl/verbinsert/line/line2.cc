#include "line.ih"

void Line::open(string const &name)
{
    delete d_in;
    d_in = new ifstream(name);
    d_input = d_in;

    if (not *d_input)
        throw string{"can't open input file `"} + name + '\'';
}
