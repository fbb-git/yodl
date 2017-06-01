#include "queue.ih"

void q_info(register Queue *qp)
{
    char *cp = qp->d_read;

    warning("Q_INFO: QUEUE CONTENTS: from: %p, read: %p, write: %p, end: %p",
                qp->d_memory, qp->d_read, qp->d_write, qp->d_memory_end);

    while (cp != qp->d_memory_end && cp != qp->d_write)
        fputc(*cp++, stderr);

    if (cp != qp->d_write)
    {
        cp = qp->d_memory;
        while (cp != qp->d_write)
            fputc(*cp++, stderr);
    }

    fputc('\n', stderr);
}
