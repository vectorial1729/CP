#include "library/template.hpp"
#include "library/string/morris_pratt.hpp"
using namespace std; 
using namespace vectorial; 
signed main() {
    long long N, K;
    read(N, K); 
    vector<long long> A(N); 
    read(A); 
    long long ans = 0; 
    if (K > 0) {
        long long prv = A[0]; 
        REP(i, 1, N) {
            long long t = 0; 
            if (A[i] <= prv) {
                t = (prv - A[i]) / K + 1; 
            }
            ans += t; 
            prv = A[i] + t * K; 
        }
    } else {
        K = -K; 
        long long nxt = A[N - 1]; 
        for (int i= N -2; i >= 0; --i) {
            long long t= 0; 
            if (A[i] >= nxt) {
                t = (A[i] - nxt) / K + 1; 
            }
            ans += t; 
            nxt = A[i] - t * K; 
        }
    }
    print(ans); 
}