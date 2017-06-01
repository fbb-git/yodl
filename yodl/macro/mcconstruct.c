#include "macro.ih"

Macro *mc_construct(char const *definition, size_t nargs)
{
    Macro *macro = (Macro *)new_memory(1, sizeof(Macro));

    stack_construct(&macro->d_definition, free);
    stack_construct(&macro->d_arg, NULL);

    macro_push(macro, definition, nargs);

    return macro;
}
