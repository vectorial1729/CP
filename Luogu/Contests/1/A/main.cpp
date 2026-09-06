#include "library/template.hpp"
using namespace std;
using namespace vectorial;

signed main() {
    long long n;
    read(n);

    if (n <= 22360) {
        print("O(n^2)");
    } else if (n <= 500000000) {
        print("O(n)");
    } else {
        print("O(1)");
    }
}