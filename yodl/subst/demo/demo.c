/*
    Compile using

    gcc demo.c ../out/library.a \
                ../../string/out/library.a \
                ../../new/out/library.a \
                ../../message/out/library.a \
                ../../root/out/library.a
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../root/root.h"
#include "../../message/message.h"
#include "../subst.h"

char buffer[80];

int main(int argc, char **argv)
{
    Subst subst;

    message_setseverity(MSG_NOTICE | MSG_ERR);

    subst_construct(&subst);            /* construct the Subst object   */

    subst_insert(&subst, "DEMO", "one", "ONE SUBST");
    subst_insert(&subst, "DEMO", "one", "TWO SUBST");
    subst_insert(&subst, "DEMO", "\\'e", "&eacute;");

    while (true)
    {
        char *cp;
        puts("Enter text: ");
        if (!fgets(buffer, 80, stdin) || buffer[0] == '\n')
            break;

        for (cp = buffer; *cp && *cp != '\n'; cp++)
        {
            printf("Inspecting char `%c': ", *cp);
            if (subst_find(&subst, *cp))
                printf("found.     Swallowed by subst\n");
            else
            {
                char *txt = new_str(subst_text(&subst));
                printf("Not found. Next returned: `%c(`%s')\n",
                        subst_get(&subst), txt ? txt : "");
                free(txt);
            }
        }
    }
}
