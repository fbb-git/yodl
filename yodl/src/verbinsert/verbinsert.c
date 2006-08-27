
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE    *input = NULL;
    char    *endlabel = 0;
    char    *indent = "";
    char    *label = 0;
    char    *progName = strrchr(argv[0], '/');
    char    *verbendl = "\n";
    char    *vindent = "";
    int     endLabelFound = 0;
    int     labelFound = 0;
    int     verbOpened = 0;
    size_t  spaces = 0;
    size_t  tabs = 0;
    size_t  verbspaces = 8;
    size_t  verbtabs = 0;
    
    if (!progName)
        progName = argv[0];
    else
        ++progName;

    while (1)
    {
        int c;
        switch(c =  getopt(argc, argv, "t:s:v:S:V:N"))
        {
            case 's':
                spaces = atoi(optarg);
            continue;

            case 't':
                tabs = atoi(optarg);
            continue;

            case 'S':
                verbspaces = atoi(optarg);
            continue;

            case 'T':
                verbtabs = atoi(optarg);
            continue;

            case 'N':
                verbendl = "";
            continue;

            case -1:
            break;

            default:
            return 1;
        }
        break;                          // only at case -1
    }

    if (argc - optind < 2)
    {
        fprintf(stderr, "usage: %s "
                        "[-n] [-s<nr>] [-t<nr>] [-S<nr>] [-T<nr>] "
                        "marker file\n"
                        "See also: `man yodlverbinsert'\n",
                        progName);
        return 1;
    }

    argv += optind;

    label = argv[0];
    endlabel =  label[1] == '/' ? "//=" : "/**/";

    input = fopen(argv[1], "r");

    if (!input)
    {
        fprintf(stderr, "Can't read `%s'\n", argv[1]);
        return 1;
    }
        
    vindent = malloc(verbtabs + verbspaces + 1);
    indent = malloc(tabs + spaces + 1);
    if (!vindent || !indent)
    {
        fprintf(stderr, "Out of memory\n");
        return 1;
    }

    memset(vindent, '\t', verbtabs);
    memset(vindent + verbtabs, ' ', verbspaces);
    vindent[verbtabs + verbspaces] = 0;
    
    memset(indent, '\t', tabs);
    memset(indent + tabs, ' ', spaces);
    indent[tabs + spaces] = 0;
    
    while (1)
    {
        char *line = NULL;
        size_t  nchars;

        if (getline(&line, &nchars, input) < 0)
            break;

//fprintf(stderr, "%s", 

        if (strstr(line, label) == line)        // matching (end)label
        {
            if (label == endlabel)              // when endlabel: done
            {
                endLabelFound = 1;
                break;
            }

            labelFound = 1;
            label = endlabel;                   // now search endlabel
            continue;
        }

        if (labelFound)
        {
            if (!verbOpened)
            {
                verbOpened = 1;
                printf("%sverb(%s", vindent, verbendl);
            }
            printf("%s%s", indent, line);
        }
        free(line);
    }

    if (!labelFound)
    {
        fprintf(stderr, "%s: label section not found\n", progName);
        return 1;
    }
    if (!endLabelFound)
    {
        fprintf(stderr, "%s: label section not ended\n", progName);
        return 1;
    }

    printf(")\n");                              // terminate verb(... by )

    return 0;
}

