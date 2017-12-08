#ifndef INCLUDED_LINETYPE_
#define INCLUDED_LINETYPE_

struct LineType
{
    enum Type
    {
        UNKNOWN   = 1 << 0,
        EMPTY     = 1 << 1,
        TEXT      = 1 << 2,
        TARGET    = 1 << 3,
        ENDTARGET = 1 << 4,
        ENDFILE   = 1 << 5,
        IGNORE    = 1 << 6,
        MASK      = (1 << 7) - 1,
    };
};
    
inline LineType::Type constexpr operator~(LineType::Type lhs)
{
    return 
        static_cast<LineType::Type>(
            static_cast<int>(LineType::MASK) & 
                                    ~static_cast<unsigned int>(lhs));
}

inline LineType::Type constexpr operator|(LineType::Type lhs, 
                                          LineType::Type rhs)
{
    return 
        static_cast<LineType::Type>(
                    static_cast<int>(lhs) | static_cast<int>(rhs));
}

inline LineType::Type constexpr operator&(LineType::Type lhs, 
                                          LineType::Type rhs)
{
    return 
        static_cast<LineType::Type>(
            static_cast<int>(lhs) & static_cast<int>(rhs));
}


#endif


