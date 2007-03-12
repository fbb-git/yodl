#include "file.ih"

void f_fullname(String *fullname, String const *filename)
{
    if (args_home())
        string_replace(fullname, "$HOME", args_home());

    string_addchar(fullname, '/');
    string_addstr(fullname, string_str(filename));
}
