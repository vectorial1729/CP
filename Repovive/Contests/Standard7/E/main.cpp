#include "library/template.hpp"
#include "library/number/modint.hpp"
#include "library/math/factorial.hpp"
using namespace std;
using namespace vectorial;
using mint = modint998244353;
int main() {
    int T; 
    read(T); 
    factorial<mint> fac;
    LOOP(T) {
        int N, M;
        read(N, M);
        vector<int> cnt(N);
        REP(i, N) {
            int a = read();
            ++cnt[a];
        }
        vector<int> xs;
        REP(x, N) {
            if (cnt[x]) {
                xs.push_back(x);
            }
        }
        if (xs.empty() or xs[0] != 0) {
            print(0);
            continue;
        }
        long long pref = 0;
        int groups = 0;
        mint ways = 1;
        mint ans = 0;
        bool ok = true;
        REP(id, xs.size()) {
            int x = xs[id];
            int c = cnt[x];
            if (pref < 2LL * x) {
                ok = false;
                break;
            }
            long long other = pref - x;
            if (id + 1 < (int) xs.size()) {
                int y = xs[id + 1];
                if (other > x) {
                    if (y != min<long long>(x + c, other)) {
                        ok = false;
                        break;
                    }
                    ++groups;
                } else {
                    int g = y - x;
                    if (c < 2 * g) {
                        ok = false;
                        break;
                    }
                    ways *= fac.binom(c, g);
                    if (c > 2 * g) {
                        ways *= 2;
                    }
                    groups += 2;
                }
                pref += c;
            } else {
                if (other > x) {
                    ++groups;
                    ans = ways * fac.binom(M, groups);
                } else {
                    ans += ways * fac.binom(M, groups + 1);
                    mint split = mint(2).pow(c) - 2;
                    ans += ways * split * fac.binom(M, groups + 2);
                }
            }
        }
        print(ok ? ans : mint(0));
    }
}