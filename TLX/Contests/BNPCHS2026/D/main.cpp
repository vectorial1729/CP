#include "library/template.hpp"
using namespace std;
using namespace vectorial;

signed main() {
    int N; 
    read(N); 
    vector<int> C(N); 
    vector<long long> W(N); 
    read(C); 
    read(W); 
    vector<vector<int>> g(N); 
    REP(i, N - 1) {
        int u, v; 
        read(u, v); 
        --u, --v; 
        g[u].push_back(v); 
        g[v].push_back(u); 

    }
    if (N == 1) {
        print(W[0]); 
        return 0; 
    }
    long long ans = 0; 
    vector<int> vis(N); 
    REP(i, N) {
        if (g[i].size() != 2) {
            ans += W[i]; 
        }
    }
    REP(s, N) {
        if (g[s].size() == 2) {
            continue; 
        }
        FOR(v0, g[s]) {
            if (g[v0].size() != 2 or vis[v0]) {
                continue; 
            }
            vector<int> path = {s}; 
            int prv = s; 
            int cur = v0; 
            while (g[cur].size() == 2) {
                vis[cur] = 1; 
                path.push_back(cur); 
                int nxt = g[cur][0]  ^ g[cur][1] ^ prv; 
                prv = cur; 
                cur = nxt; 
            }
            path.push_back(cur); 
            bool diff = false; 
            REP(i, path.size() - 1) {
                if (C[path[i]] != C[path[i + 1]]) {
                    diff = true; 
                }
            }
            if (!diff) {
                REP(i, 1, (int)path.size() - 1) {
                    ans += W[path[i]]; 
                }
                continue; 
            }
            int m = path.size(); 
            int l = 0; 
            while (l < m) {
                int r = l; 
                while (r + 1 < m and C[path[r + 1]] == C[path[l]]) {
                    ++r; 
                }
                if (l != 0 and r != m - 1) {
                    long long mn = W[path[l]]; 
                    REP(i, l + 1, r + 1) {
                        chmin(mn, W[path[i]]); 
                    }
                    ans += mn; 
                }
                l = r + 1; 
            }
        }    
    }
    print(ans); 
}
