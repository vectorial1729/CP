#include "library/template.hpp"
#include "library/transform/multiple.hpp"
using namespace std;
using namespace vectorial;

signed main() {
    int N; 
    read(N); 
    vector<long long> A(N + 1), c(N + 1, 1), d(N + 1); 
    c[0] = 0; 
    REP(i, 1, N + 1) {
        read(A[i]); 
        d[i] = -A[i]; 
    }
    multiple_transform::mobius(c); 
    multiple_transform::mobius(d); 
    long long lo = *max_element(A.begin() + 1, A.end()); 
    long long hi = numeric_limits<long long>::max(); 
    REP(i, 1, N + 1) {
        if (c[i] > 0) {
            long long x = -d[i]; 
            long long q = x >= 0 ? (x + c[i] - 1) / c[i] : x / c[i]; 
            chmax(lo, q); 
        } else if (c[i] < 0) {
            if (d[i] < 0) {
                print(-1); 
                return 0; 
            }
            chmin(hi, d[i] / -c[i]); 
        } else if (d[i] < 0) {
            print(-1); 
            return 0; 
        }
    }
    print(lo <= hi ? lo - A[1] : -1); 
}