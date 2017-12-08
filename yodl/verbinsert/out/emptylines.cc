#include "out.ih"

void Out::emptyLines(size_t nLines)
{
    if (d_line == &Out::plainLine)
        cout << string(nLines, '\n');     // insert nLines empty lines
    else
    {
        for (; nLines--; )
            numberedLine("");
    }
}
