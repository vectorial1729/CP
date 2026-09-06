#include "library/template.hpp"
using namespace std;
using namespace vectorial;

signed main() {
    int N, Q; 
    read(N, Q); 
    vector<int> P(N), A(Q), last(N + 1, -1); 
    read(P); 
    REP(q, Q) {
        read(A[q]); 
        last[A[q]] = q; 
    }
    vector<int> ans; 
    FOR(x, P) {
        if (last[x] == -1) {
            ans.push_back(x); 
        }

    }
    REP(q, Q) {
        if (last[A[q]] == q) {
            ans.push_back(A[q]); 
        }


    }
    print(ans); 
}