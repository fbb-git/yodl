#include "file.ih"

/*
    if {name} has a .yo extension by itself or if a file {name}.yo exists, 
    then use that file. 
    Otherwise if the file {name} exists, use that file
    Otherwise report failure
*/

Result f_opt_extension(String *name)
{
    register char const *ext = f_dotExtension(string_str(name));

    if 
    (
        ext &&
        strcmp(ext, DEFAULT_EXT) == 0   /* the extension is DEFAULT_EXT */
        &&
        f_isReadable(name)              /* and a readable file          */
    )
        return SUCCESS;                 /* then {name} is readable      */


    String orgName;
    string_construct(&orgName, string_str(name));
    
    string_addstr(name, DEFAULT_EXT);   /* try our default extension        */

    if (f_isReadable(name))             /* Readable: then OK                */
        return SUCCESS;

    string_swallow(name, &orgName);     /* Reset the name to the original   */
                                        /* and see if that one can be read  */
    return f_isReadable(name) ? SUCCESS : FAILED;
}
