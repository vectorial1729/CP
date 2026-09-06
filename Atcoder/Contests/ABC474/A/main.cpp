#include "library/template.hpp"
using namespace std;
using namespace vectorial;

signed main() {
    int X;
    read(X);
    REP(x, 1, 4) {
        if (x != X) {
            print(x);
            return 0;
        }
    }
}