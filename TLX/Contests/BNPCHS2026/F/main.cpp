#include "library/template.hpp"
#include "library/number/modint.hpp"
using namespace std;
using namespace vectorial;
using mint = modint998244353;

struct Edge {
    int to, w;
};

signed main() {
    int N;
    long long K;
    read(N, K);
    int lg = 31 - __builtin_clz(N);
    if (K > lg) {
        print(0);
        return 0;
    }
    vector<int> v;
    for (int l = 1; l <= N; ) {
        int q = N / l;
        v.push_back(q);
        l = N / q + 1;
    }
    int m = v.size();
    int B = sqrtl(N);

    while (1LL * (B + 1) * (B + 1) <= N) {
        ++B;
    }
    while (1LL * B * B > N) {
        --B;
    }
    auto id = [&](int x) {
        if (x <= B) {
            return m - x;
        }
        return N / x - 1;
    };
    vector<int> head(m + 1);
    vector<Edge> edges;
    edges.reserve(3200000);
    REP(i, m) {
        head[i] = edges.size();
        int x = v[i];
        for (int l = 2; l <= x; ) {
            int q = x / l;
            int r = x / q;
            if (gcd(x, q) == 1) {
                edges.push_back({
                    id(q),
                    r - l + 1
                });
            }
            l = r + 1;
        }
    }
    head[m] = edges.size();
    vector<mint> dp(m), ndp(m);
    dp[id(1)] = 1;
    REP(step, 1LL, K + 1) {
        fill(ALL(ndp), mint(0));
        int lim = 1 << step;
        REP(i, m) {
            if (v[i] < lim) {
                break;
            }
            mint sum = 0;
            REP(j, head[i], head[i + 1]) {
                auto [to, w] = edges[j];
                sum += mint(w) * dp[to];
            }
            ndp[i] = sum;
        }
        dp.swap(ndp);
    }
    print(dp[0].val());
}