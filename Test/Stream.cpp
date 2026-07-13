#include <sstream>
#include <VectorIO.h>

using namespace std;

int main()
{
    istringstream is;
    ostringstream os;

    Vector<3> v = { 1, 2, 3 };
    os << v;
    if ("{1, 2, 3}" != os.str())
    {
        cout << os.str() << endl;
        return -1;
    }

    os.str({});
    os.clear();

    os << bracket('[') << v;
    if ("[1, 2, 3]" != os.str())
    {
        cout << os.str() << endl;
        return -1;
    }

    os.str({});
    os.clear();

    Matrix<2> m = {{1, 2}, {3, 4}};
    os << m;
    if ("[\n    [1, 2],\n    [3, 4]\n]" != os.str())
    {
        cout << os.str() << endl;
        return -1;
    }

    os.str({});
    os.clear();

    os << indent(2) << bracket('{') << m;
    if ("{\n  {1, 2},\n  {3, 4}\n}" != os.str())
    {
        cout << os.str() << endl;
        return -1;
    }

    return 0;
}