#include "parser.ih"

static bool global_installed;

/*
    pp points to zeroed-struct
*/
void parser_construct(register Parser *pp,
                        register HashMap *symtab_ptr, Ostream *outs_ptr)
{
    *(char const **)&pp->d_indexName     = args_optarg('i');
    pp->d_show_nomacros = args_option('w');
    pp->d_keep_ws       = args_option('k');
    pp->d_parlist_filename = new_str("");
    stack_construct(&pp->d_paren_st, 0);        /* counts parentheses       */

    subst_construct(&pp->d_subst);
    lexer_construct(&pp->d_lexer, &pp->d_subst);
    stack_construct(&pp->d_atexit_st, free);
    stack_construct(&pp->d_string_st, 0);
    stack_construct(&pp->d_ws_level_st, 0);
                                                /* update keep ws           */
    lexer_set_keep_ws(&pp->d_lexer, true);      /* true, as ws_level is 0   */

    pp->d_string_ptr = 0;                       /* String output media      */
    pp->d_outs_ptr = outs_ptr;                  /* Ostream output media     */

    pp->d_insert = p_insert_no_chartab_ostream; /* First insert to Ostream  */
                                                /* not using chartabs       */
    stack_construct(&pp->d_insert_st, 0);       /* Stacked inserters        */

    pp->d_symtab_ptr = symtab_ptr;              /* Current symbol table     */

    pp->d_handler = ps_handlerSet[DEFAULT_SET]; /* initial parse functions  */

    stack_construct(&pp->d_handler_st, 0);      /* set up the handler stack */

    if (!global_installed)
    {
        register StackValue stValue;
        register HashItem *item;

        global_installed = true;

        item = hashmap_find(pp->d_symtab_ptr, "CHAR", BUILTIN);
        hashitem_setType(item, hashitem_type(item) | NOEXPAND_EXEC);

        p_setup_handlerSet();
        stack_construct(&ps_fun_st, 0);

        stValue.u_charp = new_str("Yodl");
        stack_push(&ps_fun_st, stValue);

        counter_insert(symtab_ptr, "XXwrotetext", 0);
    }

    if (!pp->d_indexName || !*pp->d_indexName)  /* no indexname: try -o     */
    {
                                                /* -o is not stdout         */
        *(char const **)&pp->d_indexName = args_optarg('o');
        if (pp->d_indexName && strcmp(pp->d_indexName, "-"))
        {
            String idxName;                     /* set .idx extension       */
            pp->d_indexName = file_rmExtension(pp->d_indexName);
            string_construct(&idxName, pp->d_indexName);
            free(pp->d_indexName);
            string_addstr(&idxName, ".idx");
            pp->d_indexName = string_release(&idxName);
        }
    }

    if (pp->d_indexName && *pp->d_indexName)    /* got indexname            */
    {
        pp->d_indexFile = file_open(pp->d_indexName, "w");
        return;
    }

    pp->d_indexName = 0;

    if (message_show(MSG_WARNING))
        message("No index file is created");
}
