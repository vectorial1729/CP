#include "library/template.hpp"
#include "library/transform/divisor.hpp"
using namespace std;
using namespace vectorial;

int xo(int a, int b) {
    return a ^ b;
}

signed main() {
    int N;
    read(N);
    string S;
    read(S);
    vector<int> a(N + 1);
    REP(i, N) {
        a[i + 1] = S[i] == '0';
    }
    divisor_transform::mobius<int, xo>(a);
    int ans = 0;
    REP(i, 1, N + 1) {
        ans += a[i];
    }
    print(ans);
}