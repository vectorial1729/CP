#include "library/template.hpp"
#include "library/number/modint.hpp"
using namespace std;
using namespace vectorial;
using mint = modint998244353; 
int main() {
    int T;
    read(T); 
    LOOP(T) {
       int N = read(); 
       vector<long long> A(N), B(N); 
       read(A, B); 
       vector<vector<int>> G(N); 
       REP(i, N - 1) {
        int u, v; 
        read(u, v); 
         --u, --v; 
         G[u].push_back(v); 
         G[v].push_back(u); 
       } 
       vector<int> par(N, -1), ord; 
       ord.reserve(N); 
       ord.push_back(0); 
       REP(i, N) {
        int v = ord[i]; 
        for (int u : G[v]) {
            if (u == par[v]) {
                continue; 
            }
            par[u] = v; 
            ord.push_back(u); 
        }
       }
       vector<long long> sa = A, sb = B, dp(N); 
       RREP(ii, N) {
        int v = ord[ii]; 
        vector<int> ch; 
        for (int u : G[v]) {
            if (par[u] == v) {
                ch.push_back(u); 
            }
        }
        sort(ch.begin(), ch.end(), [&](int x, int y) {return sa[x] * sb[y] < sa[y] * sb[x]; }); 
        long long cur = A[v]; 
        long long res = 0; 
        for (int u : ch) {
            res += dp[u]; 
            res += sb[u] * (cur + sa[u]); 
            cur += sa[u]; 
            sa[v] += sa[u]; 
            sb[v] += sb[u]; 
        }
        dp[v] = res; 
       }
       print(dp[0]); 
    }
}