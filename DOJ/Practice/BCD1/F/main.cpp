#include "library/template.hpp"
#include <set> 
using namespace std; 
using namespace vectorial; 
signed main() {
    string S; 
    read(S); 
    deque<pair<int, int>> q; 
    q.emplace_back(1, 1); 
    FOR(c, S) {
        if (c == 'M') {
            if (q.front().first == 0) {
                ++q.front().second; 
            } else {
                q.emplace_front(0, 1); 
            }
        } else {
            if (q.front().first == 0) {
                if (q.front().second == 1) {
                    q.pop_front(); 
                    if (q.empty()) {
                        q.emplace_front(1, 1); 
                    } else {
                        ++q.front().second; 
                    }
                } else {
                    --q.front().second; 
                    q.emplace_front(1, 1); 
                }
            } else {
                int k = q.front().second; 
                q.pop_front(); 
                if (q.empty()) {
                    q.emplace_front(1, 1); 
                } else if (q.front().second == 1) {
                    q.pop_front(); 
                    if (q.empty()) {
                        q.emplace_front(1, 1); 
                    } else {
                        ++q.front().second; 
                    }
                } else {
                    --q.front().second; 
                    q.emplace_front(1, 1); 
                }
                q.emplace_front(0, k); 
            }
        } 
        print(1 + (q.front().first == 0 ? q.front().second : 0)); 
    }
}