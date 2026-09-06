#include "library/template.hpp"
#include "library/number/mobius_function.hpp"
#include "library/number/modint.hpp"
using namespace std;
using namespace vectorial;
using mint = modint998244353; 
MobiusFunction<10000000> mu; 
signed main() {
    int N, M; 
    read(N, M); 
    mint ans = 0; 
    REP(d, 1, min(N, M) + 1) {
        long long n = N / d, m = M / d; 
        ans += mint(mu[d]) * d * d * mint(n * (n + 1) / 2) * mint(m * (m + 1) / 2); 
    }
    print(ans); 
}