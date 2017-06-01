#include "chartab.ih"

static char std_char[2];    /* initially: 1 to 1 mapping of chars */

char **ct_construct(char *table)
{
    char **chartable = new_memory(256, sizeof(char *));
    size_t idx;

    for (idx = 0; idx < 256; idx++)             /* set table to defaults */
    {
        std_char[0] = idx;
        chartable[idx] = new_str(std_char);
    }

    ct_parse_table(chartable, table);

    return chartable;
}
