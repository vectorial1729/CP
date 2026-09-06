#include "library/template.hpp"

using namespace std;
using namespace vectorial;

int main() {
    int T;
    read(T); 
    LOOP(T) {
        long long a, b, c, d;
        read(a, b, c, d); 
        bool ok =a * b == c * d ||a * c == b * d ||a * d == b * c;
        cout << (ok ? "Yes" : "No") << '\n';
    }
}