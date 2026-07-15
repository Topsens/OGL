#include <sstream>
#include <VectorIO.h>

using namespace std;

int main()
{
    ostringstream os;

    Vector<3, int> v = { 1, 2, 3 };
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

    Matrix<2, 2, int> m = {{1, 2}, {3, 4}};
    os << m;
    if ("[\n    [1, 2],\n    [3, 4]\n]" != os.str())
    {
        cout << os.str() << endl;
        return -1;
    }

    os.str({});
    os.clear();

    os << singleline << nospace << m;
    if ("[[1,2],[3,4]]" != os.str())
    {
        cout << os.str() << endl;
        return -1;
    }

    os.str({});
    os.clear();

    os << space << m;
    if ("[[1, 2], [3, 4]]" != os.str())
    {
        cout << os.str() << endl;
        return -1;
    }

    os.str({});
    os.clear();
    os << multiline;

    os << indent(2) << bracket('{') << m;
    if ("{\n  {1, 2},\n  {3, 4}\n}" != os.str())
    {
        cout << os.str() << endl;
        return -1;
    }

    istringstream("\t[ 3 , \r2 \n,1]") >> v;
    if (Any(Vector<3, int>{3, 2, 1} != v))
    {
        cout << v << endl;
        return -1;
    }

    istringstream("{{4,3},{2,1}}") >> m;
    if (Any(Matrix<2, 2, int>{{4, 3}, {2, 1}} != m))
    {
        cout << m << endl;
        return -1;
    }

    return 0;
}