#include "library/template.hpp"
using namespace std;
using namespace vectorial;

signed main() {
    long long N, M; 
    read(N, M); 
    vector<vector<pair<long long, int>>> a(60); 
    REP(i, N) {
        long long X, Y; 
        read(X, Y); 
        a[Y].push_back({X << Y ,i}); 
    }
    priority_queue<pair<long long, int>> pq; 
    __int128 sum = 0; 
    vector<int> ans; 
    REP(b, 60) {
        FOR(p, a[b]) {
            pq.push(p); 
        }
        long long need = M % (1LL << (b + 1)); 
        while (sum < need) {
            if (pq.empty()) {
                print(-1); 
                return 0; 
            }
            auto [v, i] = pq.top(); 
            pq.pop(); 
            sum += v; 
            ans.push_back(i + 1); 
        }
    }
    print(ans.size()); 
    print(ans); 

}
