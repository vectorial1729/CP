#include "library/template.hpp"
#include "library/number/linear_sieve.hpp"
#include "library/number/modint.hpp"
using namespace std;
using namespace vectorial;
using mint = modint998244353; 
signed main() {
    int N, M; 
    read(N, M); 
    int K = min(N, M); 
    LinearSieve seive(K); 
    auto & lpf = seive.get_min_prime_factor(); 
    vector<int> f(K + 1); 
    f[1] = 1; 
    mint ans = 0; 
    REP(d, 1, K + 1) {
        if (d > 1) {
            int p = lpf[d], q = d / p; 
            f[d] = q % p ? f[q] * (1 - p) : f[q]; 
        }
        long long n = N / d, m = M / d; 
        ans += mint(d) * f[d] * mint(n * (n + 1) / 2) * mint(m * (m + 1) / 2); 
    }
    print(ans); 
}