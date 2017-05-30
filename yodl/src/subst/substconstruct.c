#include "subst.ih"

void subst_construct(register Subst *sp)
{
    string_construct(&sp->d_buffer, 0);
    sp->d_action = &s_subst;
    sp->d_start_state_ptr = sp->d_current_state_ptr = s_state_new();
    sp->d_nReplacements = 0;
    sp->d_maxReplacements =  
            10000 * 
            (args_option('r') ? args_optint('r') : DEFAULT_MAX_REPLACEMENTS);
    if (sp->d_maxReplacements == 0)
        sp->d_maxReplacements = ~0 ^ 1;
}
