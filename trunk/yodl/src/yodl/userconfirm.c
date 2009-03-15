
#include "yodl.h"

bool userconfirm(char const *cmd)
{
    while (1)
    {
        int ch;

        fprintf(stderr, "Warning, live data \"%s\"\n"
                    "Execute command (y/n)? ", cmd);

        if ((ch = getchar ()) == 'y')
            return true;

        if (ch == 'n')
            return false;

        fprintf(stderr, "Enter y to execute the command,\n"
                        "Enter n to ignore the command\n");
    }
}
