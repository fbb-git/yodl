#include "yodlpost.h"

Global  global;
HashMap symtab;

/*
    The maximum linelength that can be used in index values is 500. Beyond
    that, the line is truncated and subsequent lines may be ill-formed due
    to the truncation.

    construct:
        key:    store key and rest in the returned HashItem. The key + rest
                is not used during the stack construction, but contains info
                which results in code/copy actions when the item is processed
                later on

        It receives the key and the stripped rest of the line (following the
        key). the line may be modified by the construct-functions, but is not
        owned by them. So, when the contents are to be kept, copies must be
        created locally by the construct-functions.


    handle:
    key:        redefine key's value in d_symbol
    lastnumber: assign the current lastnumber to d_section
                lastnumber is (and remains) stored in the Queue, and is
                therefore stored only once.

*/

Task task[] =
{
    {"copy",            construct_nop,          handle_copy},
    {"bodytagopt",      construct_deprecated,   handle_set},
    {"documenttype",    construct_deprecated,   handle_set},
    {"drainws",         construct_nop,          handle_drain_ws},
    {"htmldone",        construct_nop,          handle_html_done},
    {"htmllabel",       construct_label,        handle_html_label},
    {"htmlnewfile",     construct_newfile,      handle_html_newfile},
    {"htmltoc",         construct_toc,          handle_toc},
    {"htmltocentry",    construct_tocentry,     handle_html_tocentry},
    {"ignorews",        construct_nop,          handle_ignore_ws},
    {"lastnumber",      construct_lastnumber,   handle_copy},
    {"labvalue",        construct_labvalue,     handle_labvalue},
    {"mandone",         construct_nop,          handle_copy},
    {"preset",          construct_preset,       handle_nop},
    {"ref",             construct_ref,          handle_ref},
    {"set",             construct_set,          handle_set},
    {"solvelink",       construct_ref,          handle_solvelink},
    {"title",           construct_deprecated,   handle_set},
    {"txtlabel",        construct_label,        handle_nop},
    {"txtref",          construct_ref,          handle_txt_ref},
    {"txttoc",          construct_toc,          handle_txt_toc},
    {"txttocentry",     construct_txt_tocentry, handle_nop},
    {"verb",            construct_verb,         handle_verb},
    {"xmldone",         construct_xml_done,     handle_xml_done},
    {"xmllabel",        construct_label,        handle_xml_label},
    {"xmlnewfile",      construct_newfile,      handle_xml_newfile},
    {"xmlref",          construct_ref,          handle_xml_ref},
    {"xmlsolvelink",    construct_ref,          handle_xml_solvelink},
    {"xmltoc",          construct_toc,          handle_xml_toc},
    {"xmltocentry",     construct_xml_tocentry, handle_xml_tocentry},
    {0,                 0,                      0},
};

/*
    The default names may be altered using the
        INTERNALINDEX(set ...)
    command. E.g.,
        INTERNALINDEX(set previous Vorig Hoofdstuk)

    The bodytagopt, documenttype and title values may be set this way too,
    but here the direct INTERNALINDEX commands may also still be
    used. However, they are deprecated, and a corresponding message is issued
    when they are encountered.
*/
char const *default_symbols[][2] =
{
    {"previous",        "Previous Chapter"},
    {"next",            "Next Chapter"},
    {0, 0},
};

char const *section_levels[] =
{
    "",         /* UNDETERMINED_SECTION */
    "chap",
    "sect",
    "ssect",
    "sssect",
    0,
};

/*
    Dimensions:

        (no)article, SectionLevel, open/close
*/

static char const *s_empty[2]   = {"",      ""};
static char const *s_h2[]       = {"<h2>",  "</h2>"};
static char const *s_h3[]       = {"<h3>",  "</h3>"};

char const **toc_section[][sizeofSectionLevels] =
{
    {                       /* DocType: no article  */
        0,
        s_h2,               /* chapter              */
        s_h3,               /* section              */
        s_empty,            /* ssect                */
        s_empty,            /* sssect               */
    },
    {                       /* DocType: article     */
        0,
        s_empty,            /* chapter              */
        s_h2,               /* section              */
        s_h3,               /* ssect                */
        s_empty,            /* sssect               */
    }
};

char const *doctypes[] =    /* Modify this when DocType in yodlpost.h is    */
{                           /* altered                                      */
    "book",
    "report",
    "article",
    "manpage",
    "letter",
    0
};
