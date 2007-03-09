#include "hashmap.ih"

void hashmap_keys(register HashMap *map)
{
    size_t idx;

    fprintf(stderr, "There are %u active keys\n", (unsigned)map->d_n);

    for (idx = 0; idx < map->d_size; idx++)
    {
        register HashItem *atIdx = map->d_map[idx];

        switch (asHashmapValue(atIdx))
        {
            case FREE:
            continue;

            case REMOVED:
                fprintf(stderr, "   %3u: <removed>\n", (unsigned)idx);
            break;

            case ACTIVE:
                fprintf(stderr, "   %3u: `%s'\n", (unsigned)idx, atIdx->d_key);
            break;
        }
    }
    fputs("[completed]\n", stderr);
}
