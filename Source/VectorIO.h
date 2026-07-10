#ifndef _VECTOR_IO_H_
#define _VECTOR_IO_H_

#include <iostream>
#include "VectorX.h"

#ifdef VECTORX_NS
#define VXNS VECTORX_NS
namespace VECTORX_NS {
#else
#define VXNS
#endif

struct Bracket
{
    char bracket;
};

inline int bracket_index()
{
    static const int index = std::ios_base::xalloc();
    return index;
}

inline void get_bracket(std::ostream& os, char& open, char& close)
{
    switch (os.iword(bracket_index()))
    {
        case '[':
        case ']':
        {
            open  = '[';
            close = ']';
            break;
        }

        case '(':
        case ')':
        {
            open  = '(';
            close = ')';
            break;
        }

        case '<':
        case '>':
        {
            open  = '<';
            close = '>';
            break;
        }

        default:
        {
            open  = '{';
            close = '}';
            break;
        }
    }
}

inline Bracket bracket(char bracket)
{
    Bracket b;
    b.bracket = bracket;
    return b;
}

inline std::ostream& operator<<(std::ostream& os, const Bracket& bracket)
{
    os.iword(bracket_index()) = bracket.bracket;
    return os;
}

template<size_t Dims, typename Scalar>
inline std::ostream& operator<<(std::ostream& os, const Vector<Dims, Scalar>& v)
{
    char open;
    char close;
    get_bracket(os, open, close);

    os << open;

    if (Dims > 0)
    {
        os << v.s[0];

        for (size_t i = 1; i < Dims; i++)
        {
            os << ", " << v.s[i];
        }
    }

    return os << close;
}


#ifdef VECTORX_NS
}
#endif
#undef VXNS

#endif // _VECTOR_IO_H_