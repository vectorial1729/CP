#include "library/template.hpp"
#include "library/number/fast_factorize.hpp"
using namespace std;
using namespace vectorial;
signed main() {
    long long N = read(); 
    auto f = fast_factorize::factorize(N); 
    int ans = 1; 
    for (auto [p, e] : f) {
        if (e >= 2) {
            ans = 0; 
        } else {
            ans = -ans; 
        }
        
    }
    print(ans); 
}