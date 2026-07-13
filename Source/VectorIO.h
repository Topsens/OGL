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

namespace details
{
    struct Bracket
    {
        char bracket;
    };

    struct Indent
    {
        int indent;
    };

    struct SingleLine
    {
        int singleline;
    };

    inline int bracket_index()
    {
        static const int index = std::ios_base::xalloc();
        return index;
    }

    inline int indent_index()
    {
        static const int index = std::ios_base::xalloc();
        return index;
    }

    inline int singleline_index()
    {
        static const int index = std::ios_base::xalloc();
        return index;
    }

    inline void get_bracket(std::ostream& os, char& opening, char& closing)
    {
        switch (os.iword(bracket_index()))
        {
            case '[':
            case ']':
            {
                opening = '[';
                closing = ']';
                break;
            }

            case '(':
            case ')':
            {
                opening = '(';
                closing = ')';
                break;
            }

            case '<':
            case '>':
            {
                opening = '<';
                closing = '>';
                break;
            }

            default:
            {
                opening = '{';
                closing = '}';
                break;
            }
        }
    }

    inline int get_indent(std::ostream& os)
    {
        auto indent = os.iword(indent_index());
        return indent >= 1 ? indent - 1 : 4;
    }

    inline char read(std::istream& is)
    {
        char c;
        while ([&]{ is >> c; return c == ' ' || c == '\n' || c == '\r' || c == '\t'; }());
        return is ? c : 0;
    }

    inline char peek(std::istream& is)
    {
        char c;
        while ([&]{ c = (char)is.peek(); return c == ' ' || c == '\n' || c == '\r' || c == '\t'; }())
        {
            is.get();
        }
        return is ? c : 0;
    }
}

inline details::Bracket bracket(char bracket)
{
    details::Bracket b;
    b.bracket = bracket;
    return b;
}

inline details::Indent indent(int indent)
{
    details::Indent i;
    i.indent = indent < 1 ? 1 : indent + 1;
    return i;
}

inline std::ostream& operator<<(std::ostream& os, const details::Bracket& bracket)
{
    os.iword(details::bracket_index()) = bracket.bracket;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const details::Indent& indent)
{
    os.iword(details::indent_index()) = indent.indent;
    return os;
}

template<size_t Dimensions, typename Scalar>
inline std::ostream& operator<<(std::ostream& os, const Vector<Dimensions, Scalar>& v)
{
    char opening;
    char closing;
    details::get_bracket(os, opening, closing);

    os << opening;

    if (Dimensions > 0)
    {
        os << v.s[0];

        for (size_t i = 1; i < Dimensions; i++)
        {
            os << ", " << v.s[i];
        }
    }

    return os << closing;
}

template<size_t MRows, size_t MCols, typename Scalar>
inline std::ostream& operator<<(std::ostream& os, const Matrix<MRows, MCols, Scalar>& m)
{
    char opening;
    char closing;
    details::get_bracket(os, opening, closing);

    int singleline = os.iword(details::singleline_index());

    os << opening;

    if (!singleline)
    {
        os << std::endl;
        for (int i = 0; i < details::get_indent(os); i++)
        {
            os << ' ';
        }
    }

    if (MRows > 0)
    {
        os << m[0];

        for (size_t i = 1; i < MRows; i++)
        {
            os << ',';
            if (!singleline)
            {
                os << std::endl;
                for (int i = 0; i < details::get_indent(os); i++)
                {
                    os << ' ';
                }
            }
            os << m[i];
        }
    }

    if (!singleline)
    {
        os << std::endl;
    }

    return os << closing;
}

template<size_t Dimensions, typename Scalar>
inline std::istream& operator>>(std::istream& is, Vector<Dimensions, Scalar>& v)
{
    char closing = 0;

    switch (details::read(is))
    {
        case '{':
        {
            closing = '}';
            break;
        }

        case '[':
        {
            closing = ']';
            break;
        }

        case '(':
        {
            closing = ')';
            break;
        }

        case '<':
        {
            closing = '<';
            break;
        }

        default:
        {
            is.setstate(ios::failbit);
            return is;
        }
    }

    if (Dimensions > 0)
    {
        is >> v.s[0];

        for (size_t i = 1; i < Dimensions; i++)
        {
            char c = details::read(is);
            if (',' != c)
            {
                is.setstate(ios::failbit);
                return is;
            }
            is >> v.s[i];
        }
    }

    if (closing != details::read(is))
    {
        is.setstate(ios::failbit);
    }

    return is;
}

template<size_t MRows, size_t MCols, typename Scalar>
inline std::istream& operator>>(std::istream& is, Matrix<MRows, MCols, Scalar>& m)
{
    char closing = 0;

    switch (details::read(is))
    {
        case '{':
        {
            closing = '}';
            break;
        }

        case '[':
        {
            closing = ']';
            break;
        }

        case '(':
        {
            closing = ')';
            break;
        }

        case '<':
        {
            closing = '<';
            break;
        }

        default:
        {
            is.setstate(ios::failbit);
            return is;
        }
    }

    if (MRows > 0)
    {
        is >> m.v[0];

        for (size_t i = 1; i < MRows; i++)
        {
            char c = details::read(is);
            if (',' != c)
            {
                is.setstate(ios::failbit);
                return is;
            }
            is >> m.v[i];
        }
    }

    if (closing != details::read(is))
    {
        is.setstate(ios::failbit);
    }

    return is;
}

#ifdef VECTORX_NS
}
#endif
#undef VXNS

#endif // _VECTOR_IO_H_