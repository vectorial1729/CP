#include "library/template.hpp"
using namespace std; 
using namespace vectorial; 
signed main() {
    int N; 
    read(N); 
    string S; 
    read(S); 
    int ans =N + 1; 
    REP(c, 2) {
        char x = '0' + c; 
        int l = -1, r = -1, cnt = 0; 
        REP(i, N) {
            if (S[i] != x) {
                continue; 
            }
            if (l == -1) {
                l = i; 
            }
            r = i; 
            ++cnt; 
        }
        if (cnt >= 2) {
            chmin(ans, l + (N - 1 - r)); 
        }
    }
    print(ans == N + 1 ? -1 : ans); 
}