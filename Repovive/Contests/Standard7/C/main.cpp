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
        vector<int> C(N); 
        read(C); 
        vector<mint> sum(N + 1); 
        mint tot = 0, ans = 0; 
        for (int c : C) {
            mint dp = 1 + tot - sum[c]; 
            tot += dp; 
            sum[c] += dp; 
            ans = dp; 
        }
        print(ans); 
    }
}