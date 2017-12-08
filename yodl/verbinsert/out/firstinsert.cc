#include "out.ih"

void Out::firstInsert(std::string const &line)
{
    cout << d_vindent << "verb(" << d_verbEndl;
    d_insert = d_line;
    insert(line);
}
