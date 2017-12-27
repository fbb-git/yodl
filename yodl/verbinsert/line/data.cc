#include "line.ih"

regex Line::s_markerBegin
    {    
        "(" R"(^//\+?[^[:blank:]]+$)"       ")|"
        "(" R"(^/\*\+?[^[:blank:]]+\*/$)"   ")"
    };

regex Line::s_markerEnd
    {    
        "(" "^//=$"                         ")|"
        "(" R"(^/\*\*/$)"                   ")"
    };

