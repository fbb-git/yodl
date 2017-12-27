#include "parser.ih"

        // return value: separating operator
void p_value(register Parser *pp, Term *term)
{
    bool negative = false;

    while (*term->text == '-')              // skip unary minus operators
    {
        negative = !negative;
        ++term->text;
    }

    char *cp = strpbrk(term->text, "+-");   // find an operator

    if (cp == 0)                            // not found
        term->binop = 0;
    else
    {
        term->binop = *cp;              // save it for parser_value
        *cp = 0;                        // end the text for p_compute
    }

    p_compute(pp, term);

    if (negative)                       // negate a negative value
        term->value = -term->value;

    if (cp != 0)                        // found an operator
    {
        *cp = term->binop;              // reset the operator
        term->text = cp + 1;            // next term starts beyond the binop
    }
}
    

