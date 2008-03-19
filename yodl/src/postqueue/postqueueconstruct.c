#include "postqueue.ih"

/*
    When processing the index Q, the lines start with keywords to the
    tasks to be executed. These keywords are looked up in the taskmap hashmap
    returning a pointer to a task-structure.

    The constructor element in the task structure is then called to produce a
    hashitem containing the particulars about the task. It receives the key
    and the stripped rest of the line.

    It is then stored in the list of tasks to be processed by the handler
    functions.

    It is also possible that the constructor can't do its job. In that case
    it returns 0, which value is then ignored. It's up to the constructor to
    generate a warning or error in those cases. If errors occurred, then the
    queue is not processed.
*/

void  postqueue_construct(Task *task)
{
    size_t lineNr = 0;
    size_t maxLength = args_option('l') ? args_optint('l') : 1000;
    char *line = new_memory(maxLength, sizeof(char));
    char *key = new_memory(maxLength,  sizeof(char));
    char const *fileName = args_arg(0);
    FILE *findex;
    HashMap taskmap;

    findex = file_open(fileName, "r");
    message_setfilename(fileName);
    hashmap_construct(&taskmap);                    /* create the task-map  */

    while (task->d_key)
    {
        HashItem *item = hashitem_construct(ANY, task->d_key,
                                        (void *)task, root_nop);
        hashmap_insert(&taskmap, item);
        task++;
    }

    while (1)
    {
        HashItem *taskStructPtr;
        HashItem *item;
        Task *taskPtr;
        long offset;
        int nread;
        char *stripped;

        line[maxLength - 1] = ' ';            /* this char should not */
                                                    /* be overwritten or    */
                                                    /* a line may have been */
                                                    /* read incompletely    */

        if (!fgets(line, maxLength, findex))     /* get index commands*/
            break;

        message_setlineno(++lineNr);
                                                        /* get the line's   */
                                                        /* essential parts  */
        if (sscanf(line, "%ld %s%n", &offset, key, &nread) != 2)
        {
            warning("Line `%s' ignored", line);
            continue;
        }

        if 
        (
            line[maxLength - 1] == 0              /* line fills up    */
            &&                                          /* the complete     */
            line[maxLength - 1] != '\n'           /* buffer, without  */
        )                                               /* reaching the end */
        {
            warning(" INTERNAL BUFFER TOO SMALL FOR LONG LINE.\n"
                "Rerun %s with a larger -l option setting than -l %u.\n"
                "The line is truncated to: `%s'\n",
                args_programName(), maxLength, line);

            while                                       /* skip the rest    */
            (
                fgetc(findex) != '\n' && !feof(findex)
            )
                ;
        }

                                                        /* find taskstruct  */
        taskStructPtr = hashmap_find(&taskmap, key, ANY);

        if (taskStructPtr == PFAILED)                   /* no such task:    */
        {                                               /* that's an error  */
            message_show(MSG_ERR);
            message("%s: %s no defined task", args_programName(), key);
            continue;
        }
        taskPtr =  (Task *)hashitem_value(taskStructPtr);

        stripped = line + nread;
        string_strip(&stripped);
                                                    /* if constructor fails */
                                                    /* continue             */
        if (!(item =  (*taskPtr->d_constructor)(key, stripped)))
            continue;

        pq_append(offset, item, taskPtr->d_handler);
    }
    fclose(findex);                 /* The index is now processed       */
    free(key);
    free(line);

    if (message_errors())
    {
        message("Terminating %s due to error(s) in `%s'.", args_programName(),
                                                           args_arg(1));
        exit(1);
    }
                                    /* Open Yodl's output file to read  */
    postQueue.d_istream = file_open(args_arg(1), "r");
    message_setfilename(args_arg(1));
    message_setlineno(0);
}
