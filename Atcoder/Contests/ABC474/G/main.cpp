#include "library/template.hpp"
#include "library/transform/multiple.hpp"
using namespace std;
using namespace vectorial;

signed main() {
    int T; 
    read(T); 
    LOOP(T) {
        long long N, K;
        read(N, K); 
        long long mx = (1LL * N * N - 1) / 2; 
        if (N % 2 == 0 || K < N - 1 || K > mx || K % 2 ){
            print("No");
            continue; 
        }
        int m = (N -1 ) / 2; 
        long long q = (K - (N - 1)) / 2; 
        int a = min<long long> (q / m, m - 1); 
        int b = q - 1LL * a * m; 
        string S; 
        S.reserve(1LL * N * N - 1); 
        auto add = [&](char c, int n) {
            S.append(n, c); 
        }; 
        REP(_, a) {
            add('R', N - 1); 
            add('D', 1); 
            add('L', N - 1); 
            add('D', 1); 
        }
        add('R', 2 * b); 
        add('D', 1); 
        add('L', 2 * b); 
        int h1 = N - 2 * a - 2; 
        int w1  = 2 * b + 1; 
        add('D', h1); 
        REP(j, 1, w1) {
            add('R', 1); 
            add(j % 2 ? 'U' : 'D', h1-1); 
        }
        int h2 = N - 2 * a; 
        int w2 = N - w1; 
        if (w2) {
            add('R', 1); 
            add('U', h2 - 1); 
            REP(j, 1, w2) {
                add('R', 1); 
                add(j % 2 ? 'D' : 'U', h2 - 1); 
            }
        }
        print("Yes"); 
        print(S); 
    }
}