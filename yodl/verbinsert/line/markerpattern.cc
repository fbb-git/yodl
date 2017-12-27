#include "line.ih"

bool Line::markerPattern()
{
    smatch result;
                                            // first match the end target
                                            // 'ignore' is set at, e.g., -A
    if (regex_match(d_line, result, s_markerEnd))
    {
        d_type = d_ignore ? IGNORE : ENDTARGET;
        return true;
    }
                                            // no end target: match targets
    if (regex_match(d_line, result, s_markerBegin))
    {
        if (result[0] != d_target)          // no target, so it's text
            d_type = d_ignore ? IGNORE : TEXT;
        else if (d_target[2] != '+')        // target w/o +, so std. target
            d_type = d_ignore ? IGNORE : TARGET;
        else
        {                                   // `+' target, toggle begin/end
            d_type = d_begin ? TARGET : ENDTARGET;
            d_begin = not d_begin;
        }

        return true;
    }

    return false;
}

/*
    If end-marker is matched, ignore (-A, //+...) or return ENDTARGET
    At //+ target specifications: ignore all markers, toggle TARGET and
        ENDTARGET if line == target
    If a line matches a begin marker, but not the non //+ target, then return
        it as text, or IGNORE if -A was specified
*/
    



