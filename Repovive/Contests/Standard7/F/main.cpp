#include "library/template.hpp"
#include "library/number/modint.hpp"
#include "library/math/factorial.hpp"
using namespace std;
using namespace vectorial;
using mint = modint998244353;
int main() {
    int T; 
    read(T); 
    factorial<mint> fac;
    LOOP(T) {
        int N; 
        read(N); 
        vector<long long> X(N); 
        vector<int> D(N); 
        read(X); 
        read(D); 
        vector<int> cut(N + 1); 
        long long pref = 0; 
        REP(i, 1, N) {
            pref += D[i - 1]; 
            cut[i] = max(pref - 2LL * (i - 1), 2LL * i - pref); 
        }
        vector<int> st; 
        st.reserve(N * 2); 
        vector<pair<int, int>> ans; 
        ans.reserve(N - 1); 
        REP(i, N) {
            int delta = cut[i + 1] - cut[i]; 
            int L = (D[i] - delta) / 2; 
            int R = D[i] - L; 
            REP(_, L ){
                int j = st.back(); 
                st.pop_back(); 
                ans.emplace_back(j, i); 

            }
            REP(_, R) {
                st.push_back(i); 
            }
        }
        for (auto[u, v] : ans) {
            print(u + 1, v + 1); 
        }
    }
}