#include "library/template.hpp"
#include "library/algorithm/maximum_rectangle.hpp"
#include "library/datastructure/cartesian_tree.hpp"
#include "library/datastructure/segment_tree/li_chao_segment_tree.hpp"
#include "library/datastructure/segment_tree/commutative_dual_segment_tree.hpp"
#include <set> 
using namespace std; 
using namespace vectorial; 
long long mappint(long long f, long long x) {
    return max(f, x); 
}
long long composition(long long f, long long g) {
    return max(f, g); 
}
long long id_max() {
    return 0; 
}
vector<long long> solve_prefix(const vector<long long> & A) {
    int N = A.size(); 
    vector<long long> X(N); 
    REP(i, N) {
        X[i] = i + 1; 
    }
    LiChaoSegmentTree<long long, false> seg(X); 
    auto ranges= MinCartesianTreeBuilder::build(A).ranges(); 
    REP(i, N) {
        auto[l, r] = ranges[i]; 
        seg.add_segment(i + 1, r, A[i], -A[i] * l); 
    }
    vector<long long> res(N + 1); 
    REP(r, 1, N + 1) {
        res[r] = res[r - 1]; 
        if (auto v  = seg.query(r)) {
            chmax(res[r], *v); 
        }
    }
    return res; 
}

signed main() {
    long long N, X; 
    read(N, X); 
    vector<long long> A(N); 
    read(A); 
    vector<long long> pre = solve_prefix(A); 
    vector<long long> rev = A; 
    reverse(ALL(rev)); 
    vector<long long> rpre = solve_prefix(rev); 
    vector<long long> suf(N + 1); 
    REP(k, N + 1) {
        suf[k] = rpre[N - k]; 
    }
    vector<long long> H = A; 
    FOR(h, H) {
        chmin(h, X); 
        
    }
    CommutativeDualSegmentTree<long long, long long, mappint, composition, id_max> cross(N + 1, X); 
    maximal_rectangles_hist(H, [&](int l,int r, long long h) {
        cross.apply(l, r + 1, h * (r - l + 1LL)); 
    });
    REP(k, N + 1) {
        print(max({pre[k], suf[k], cross[k]})); 
    } 
}