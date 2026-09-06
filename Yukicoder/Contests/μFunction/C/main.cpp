#include "library/template.hpp"
#include "library/number/sum_of_mobius_function.hpp"
using namespace std;
using namespace vectorial;
signed main() {
    long long N = read(); 
    SumOfMobiusFunction<long long> mu(N); 
    print(mu()); 
}