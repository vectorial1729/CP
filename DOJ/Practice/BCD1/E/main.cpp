#include "library/template.hpp"
#include <set> 
using namespace std; 
using namespace vectorial; 
signed main() {
    long long N, R, K, Q; 
    read(N, R, K, Q); 
    vector<long long> A(N); 
    read(A); 
    vector<multiset<long long>> st(R); 
    int cnt = 0, bad = 0; 
    long long sum = 0; 
    auto del_state= [&](int r) {
        if (st[r].empty()) {
            return; 
        }
        --cnt; 
        if (*st[r].begin() != *st[r].rbegin()) {
            --bad;
        } else {
            sum -= *st[r].begin(); 
        }
    }; 

    auto add_state = [&](int r) {
        if (st[r].empty()) {
            return; 
        }
        ++cnt; 
        if (*st[r].begin() == *st[r].rbegin()) {
            sum += *st[r].begin(); 
        } else {
            ++bad; 
        }
    }; 
    auto add = [&](int i, long long x) {
        int r = i % R; 
        del_state(r); 
        st[r].insert(x); 
        add_state(r); 
    }; 
    auto del = [&](int i, long long x) {
        int r = i % R; 
        del_state(r); 
        st[r].erase(st[r].find(x)); 
        add_state(r); 
    }; 
    REP(i, N) {
        if (A[i] != -1) {
            add(i, A[i]); 
        }

    }
    auto ok = [&]() {
        if (bad) {
            return false; 
        }
        if (cnt < R) {
            return true; 
        }
        return sum == K; 
    }; 
    LOOP(Q) {
        int t, i; 
        read(t, i); 
        --i; 
        if (A[i] != -1) {
            del(i, A[i]); 
        }
        if (t == 1) {
            long long x; 
            read(x); 
            A[i] = x; 
            add(i, x); 
        } else {
            A[i] = -1; 
        }
        print(ok() ? YES : NO); 
    }
}