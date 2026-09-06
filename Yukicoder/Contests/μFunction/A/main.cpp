#include "library/template.hpp"
#include "library/number/mobius_function.hpp"
#include "library/number/modint.hpp"
using namespace std;
using namespace vectorial;
using mint = modint998244353; 
signed main() {
    int N, M; 
    read(N, M); 
    int K = min(N, M); 
    MobiusFunction<1000> mu; 
    vector<mint> f(K + 1); 
    REP(d, 1, K + 1) {
        if (mu[d]) {
            for (int k = d; k <= K; k += d) {
                f[k] += mint(mu[d]) * d; 
            }
        }
    }
    mint ans  = 0; 
    REP(d, 1, K + 1) {
        long long n = N / d, m = M / d; 
        ans += mint(d) * f[d] * (n * (n + 1) / 2) * (m * (m + 1) / 2); 
    }
    print(ans); 
}