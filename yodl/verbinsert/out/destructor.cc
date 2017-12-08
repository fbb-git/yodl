#include "out.ih"

Out::~Out()
{
    if (d_nLines)
        cout << d_vindent << ")\n";
}
