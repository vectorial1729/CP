#include "library/template.hpp"
using namespace std;
using namespace vectorial;

signed main() {
    int N; 
    read(N); 
    vector<long long> A(N), B(N); 
    read(A, B); 
    int p = -1; 
    REP(i, N) {
        if (A[i] > B[i]) {
            p = i; 
            break; 
        }
    }
    if (p == -1) {
        print("No"); 
        return 0; 
    }
    vector<long long> W(N, 1); 
    W[p] = 1000000000000000000LL; 
    print("Yes"); 
    print(W); 
}