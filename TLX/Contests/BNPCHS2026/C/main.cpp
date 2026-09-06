#include "library/template.hpp"
using namespace std;
using namespace vectorial;

signed main() {
    int N, Q; 
    read(N, Q); 
    vector<int> A(N); 
    read(A); 
    string S; 
    read(S); 
    int p = -1; 
    REP(i, Q) {
        if (S[i] != 'R') {
            p = i; 
            break; 
        }
    }
    if (p == -1) {
        int rev = 0; 
        FOR(c, S) {
            rev ^= 1; 
        }
        if (rev) {
            reverse(ALL(A)); 

        }
        print(A); 
        return 0; 
    }
    int rev = 0; 
    REP(i, p) {
        if (S[i] == 'R') {
            rev ^= 1; 
        }
    }
    if (rev) {
        reverse(ALL(A)); 

    } 
    if (S[p] == 'O') {
        REP(i, 1, N) {
            A[i] |= A[i - 1]; 
        }

    } else {
        REP(i, 1, N) {
            A[i] &= A[i - 1];
        }
    }
    array<int, 30> l, r; 
    l.fill(N); 
    r.fill(-1); 
    REP(i, N) {
        REP(b, 30) {
            if (A[i] >> b & 1) {
                chmin(l[b], i); 
                chmax(r[b], i); 
            }
        }
    }
    for (int i= p + 1; i < Q; ++i) {
        if (S[i] == 'R') {
            REP(b, 30) {
                if (r[b] == -1) {
                    continue; 
                }
                int nl = N - 1 - r[b]; 
                int nr = N - 1 - l[b]; 
                l[b] = nl; 
                r[b] = nr; 
            }
        } else if (S[i] == 'O') {
            REP(b, 30) {
                if (r[b] != -1) {
                    r[b] = N - 1; 
                }
            }
        } else {
            REP(b, 30) {
                if (l[b] != 0) {
                    l[b] = N; 
                    r[b] = -1; 
                }
            }
        }
    }
    vector<int> ans(N); 
    REP(b, 30) {
        if (r[b] == -1) {
            continue; 
        }
        REP(i, l[b], r[b] + 1) {
            ans[i] |= 1 << b; 
        }
    }
    print(ans); 
}
