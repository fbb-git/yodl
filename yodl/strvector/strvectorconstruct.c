#include "strvector.ih"

void strVector_construct(StrVector *strVector)
{
    memset(strVector, 0, sizeof(StrVector));
}
