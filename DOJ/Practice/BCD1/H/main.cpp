#include "library/template.hpp"
#include <set> 
using namespace std; 
using namespace vectorial; 
using Mat = array<array<long long, 2>, 2>; 
constexpr long long INF = 1LL << 62; 
Mat id() {
    return {{{0, -INF}, {-INF, 0}}}; 
}
Mat merge(const Mat& a, const Mat& b) {
    Mat c; 
    REP(i, 2) {
        REP(j, 2) {
            c[i][j] = -INF; 
            REP(k, 2) {
                chmax(c[i][j], b[i][k] + a[k][j]); 
            }
        }
    }
    return c; 
}
Mat one(bool f7, bool l6) {
    Mat a = id(); 
    int t =l6; 
    chmax(a[t][0], 1LL); 
    if (!f7) {
        chmax(a[t][1], 1LL); 
    }
    return a; 
}
signed main() {
    long long N; 
    read(N); 
    string S = to_string(N); 
    int L = S.size(); 
    Mat dp[20][2][2]; 
    REP(a, 2) {
        REP(b, 2) {
            dp[0][a][b] = one(a, b); 
        }
    }
    REP(len, 1, 20) {
        REP(a, 2) {
            REP(b, 2) {
                dp[len][a][b] = id(); 
                REP(d, 10) {
                    if (b && d == 7) {
                        continue; 
                    }
                    dp[len][a][b] = merge(dp[len][a][b], dp[len - 1][a][d == 6]); 
                }
            }
        }
    }
    Mat all = id(); 
    REP(len, 1, L) {
        REP(d, 1, 10) {
            all = merge(all, dp[len - 1][d == 7][d == 6]); 
        }
    }
    Mat cur = id(); 
    bool first7 = false; 
    bool prev6 = false; 
    bool bad = false; 
    REP(i, L) {
        int lim = S[i] - '0'; 
        int lo = i == 0 ? 1 : 0; 
        int rem = L - i - 1; 
        REP(d, lo, lim) {
            if (i == 0) {
                cur = merge(cur, dp[rem][d == 7][d == 6]); 
            } else if (!bad && !(prev6 && d == 7)) {
                cur = merge(cur, dp[rem][first7][d == 6]); 
            }
        }
        if (i == 0) {
            first7 = lim == 7; 
            prev6 = lim == 6; 
        } else {
            bad |= prev6 && lim == 7; 
            prev6 = lim == 6; 
        }
    }
    if (!bad) {
        cur = merge(cur, one(first7, prev6)); 
    }
    all = merge(all, cur); 
    long long keep = max(all[0][0], all[1][0]); 
    print(N - keep); 
}