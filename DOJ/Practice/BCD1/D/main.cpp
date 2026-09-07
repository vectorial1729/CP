#include "library/template.hpp"
using namespace std; 
using namespace vectorial; 
signed main() {
    long long A, B; 
    read(A, B); 
    print(A + B - gcd(A, B)); 
}