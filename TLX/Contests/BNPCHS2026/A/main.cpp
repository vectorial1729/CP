#include "library/template.hpp"
using namespace std;
using namespace vectorial;

signed main() {
    string S; 
    read(S); 
    int n = S.size(); 
    if (n % 2 ) {
        print(0); 
        return 0; 
    }   
    REP(i, n / 2) {
        if (S[i] != S[n - 1- i]) {
            print(0); 
            return 0; 
        }
    }
    int ans = 1, len = n; 
    while (len % 4 == 0) {
        bool ok = true; 
        REP(i, len / 2) {
            if (S[i] != S[i + len / 2]) {
                ok =false; 
                break; 
            }
        }
        if (!ok) {
            break; 
        }
        ++ans; 
        len /= 2; 
    }
    print(ans); 
}