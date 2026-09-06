#include "library/template.hpp"
using namespace std;
using namespace vectorial;

signed main() {
    int N;
    read(N);
    vector<int> P(N);
    read(P);
    REP(i, N) {
        if ((P[i] - 1) / 10 != i / 10) {
            print("No");
            return 0;
        }
    }
    print("Yes");
}