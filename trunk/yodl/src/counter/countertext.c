#include "counter.ih"

static char valueText[40];

char const *counter_text(HashItem *item)
{
    snprintf(valueText, 40, "%d", counter_value(item));
    return valueText;
}
