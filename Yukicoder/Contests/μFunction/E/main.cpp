#include "library/template.hpp"
#include "library/number/mobius_function.hpp"
using namespace std;
using namespace vectorial;
MobiusFunction<10000000> mu; 
signed main() {
    int N, M; 
    read(N, M); 
    long long ans = 0; 
    REP(d, 1, min(N, M) + 1) {
        ans += 1LL * mu[d] * (N / d) * (M / d);

    }
    print(ans); 
}