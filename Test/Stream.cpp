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
        return -1;
    }

    os.str({});
    os.clear();
    os << bracket('[') << v;
    if ("[1, 2, 3]" != os.str())
    {
        return -1;
    }

    return 0;
}