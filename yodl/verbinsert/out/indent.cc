#include "out.ih"

void Out::indent(string &target, size_t count, int ch)
{
    switch (ch)
    {
        case ' ':
            target += string(count, ' ');
        break;
        
        case '\t':
            target.insert(0, count, '\t');
        break;
    }
}
