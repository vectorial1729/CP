#include "library/template.hpp"
#include "library/string/morris_pratt.hpp"
using namespace std; 
using namespace vectorial; 
signed main() {
    int N, M; 
    read(N, M); 
    string S; 
    read(S); 
    string P = morris_pratt::min_period(S); 
    string T(M, 'a'); 
    REP(i, M) {
        T[i] =P[i % P.size()]; 
    }
    print(T); 
}