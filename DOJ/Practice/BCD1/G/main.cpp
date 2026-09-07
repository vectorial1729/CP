#include "library/template.hpp"
#include <set> 
using namespace std; 
using namespace vectorial; 
signed main() {
    long long N, M; 
    read(N, M); 
    REP(i, N) {
        long long x; 
        read(x); 
    }
    long long m = M; 
    int q = 0; 
    while ((m & 1) == 0) {
        m >>= 1; 
        ++q; 
    } 
    int D = N - 1 - q; 
    if (D < 2) {
        print(NO); 
        return 0; 
    }
    vector<pair<long long, int>> P; 
    P.reserve(D); 
    long long x = 1 % m; 
    REP(i, 1, D + 1) {
        x = x * 2 % m; 
        P.emplace_back(x, i); 
    }
    sort(ALL(P)); 
    int l = 0, r = D - 1; 
    while (l <r) {
        long long s= P[l].first + P[r].first; 
        if (s == m - 1) {
            int u = P[l].second; 
            int v = P[r].second; 
            if (u > v) {
                swap(u, v); 

            }
            print(YES); 
            print(q + 1, q + u + 1, q + v + 1); 
            return 0; 
        }
        if (s < m - 1) {
            ++l; 
        } else {
            --r; 
        }


    }
    print(NO); 
}