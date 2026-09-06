#include "library/template.hpp"

using namespace std;
using namespace vectorial;

int main() {
    int T;
    read(T); 
    LOOP(T) {
        int N = read(); 
        long long sa = 0, sb = 0; 
        long long ma = 0 ,mb = 0; 
        REP(i, N) {
            long long a; 
            string s; 
            read(a, s); 
            if (s == "A") {
                sa += a; 
                chmax(ma, a); 
            } else {
                sb += a; 
                chmax(mb, a); 
            }
        }
        print(max({sa + sb, sa + ma, sb + mb})); 
    }
}