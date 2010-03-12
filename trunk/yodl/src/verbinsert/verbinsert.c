#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

/* tailored getline() after the Debian Linux manpage about getline()    */
/* tailored in the sense that no tests for str and n being NULL are     */
/* performed, and it may be assumed that *str == NULL                   */
/* This function was added because some systems don't offer             */
/* a getline() implementation for C                                     */

static size_t const bufsize = 100;

static void check_memory(void const *s)
{
    if (!s) 
    {
        fprintf(stderr, "Out of memory!\n");
        exit(1);
    }
}

static ssize_t y_getline(char **str, size_t *n, FILE *in) 
{
    char *dest = malloc(bufsize);           /* realloc ok for initial buf   */
    ssize_t size = 0;                       /* nothing read yet             */

    check_memory(dest);

    while (fgets(dest + size, (int)bufsize, in)) /* read until \n or EOF    */
    {   
                                            /* check for \n: done if found  */
        char *newline = strchr(dest + size, '\n');
        if (newline)
        {
            size = newline - dest + 1;      /* at \n: `size' is # chars read */
            break;
        }
        size += bufsize - 1;                /* max # chars read */
                                            /* expand `dest' by bufsize     */
        check_memory(dest = realloc(dest, size + bufsize));
    }

    *str = dest;
    *n = size;
    return size == 0 ? -1 : size;       /* -1 must also be returned on EOF  */
                                        /* i.e., when 0 chars were read     */
}

int main(int argc, char **argv)
{
    FILE    *input = NULL;
    char    *endlabel = 0;
    char    *indent = 0;
    char    *label = 0;
    char    *progName = strrchr(argv[0], '/');
    char    *verbendl = "\n";
    char    *vindent = 0;
    int     endLabelFound = 0;
    int     labelFound = 0;
    int     verbOpened = 0;
    size_t  labelsize = 0;
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
        break;                          /* only at case -1 */
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
    labelsize = strlen(label);

    input = fopen(argv[1], "r");

    if (!input)
    {
        fprintf(stderr, "Can't read `%s'\n", argv[1]);
        return 1;
    }
        
    check_memory(vindent = malloc(verbtabs + verbspaces + 1));
    check_memory(indent = malloc(tabs + spaces + 1));

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

        if (y_getline(&line, &nchars, input) < 0)
            break;

        if 
        (
            strstr(line, label) == line         /* matching (end)label */
            &&
            isspace((unsigned char)line[labelsize])
        )
        {
            if (label == endlabel)              /* when endlabel: done */
            {
                endLabelFound = 1;
                break;
            }

            labelFound = 1;
            label = endlabel;                   /* now search endlabel */
            labelsize = strlen(endlabel);
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

    fclose(input);                              /* to make cppcheck happy */
    free(indent);
    free(vindent);

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

    printf(")\n");                              /* terminate verb(... by ) */

    return 0;
}

