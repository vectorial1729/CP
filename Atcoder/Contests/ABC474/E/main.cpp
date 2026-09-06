#include "library/template.hpp"
#include "library/datastructure/fenwick_tree/fenwick_tree.hpp"
#include "library/datastructure/fenwick_tree/fenwick_tree_set.hpp"
using namespace std;
using namespace vectorial;

signed main() {
    int T; 
    read(T); 
    LOOP(T) {
        int N; 
        read(N); 
        vector<long long> A(N), B(N), D(N); 
        vector<int> ids(N), rank(N); 
        vector<pair<long long, int>> ord(N); 
        long long sumB = 0; 
        REP(i, N) {
            read(A[i], B[i]); 
            D[i] = A[i] - B[i]; 
            sumB += B[i]; 
            ids[i] = i; 
            ord[i] = {D[i], i}; 
        }
        sort(ALL(ord)); 
        REP(i, N) {
            rank[ord[i].second] = i; 
        }
        sort(ALL(ids), [&](int i, int j) {return A[i] > A[j]; });
        fenwick_tree_set st(N); 
        FenwickTree<long long> fw(N); 
        long long ans = 1LL << 62; 
        for (int l = 0; l < N; ) {
            int r = l; 
            long long c = A[ids[l]];
            while (r < N && A[ids[r]] == c) {
                int i = ids[r++]; 
                st.insert(rank[i]); 
                fw.add(rank[i], D[i]); 
            } 
            int h = N / 2; 
            int k = max(0, h - 1); 
            int p = lower_bound(ALL(ord), pair<long long, int> { 2 * c, -1}) - ord.begin(); 
            int cnt = st.count_lt(p); 
            long long sum = fw.sum(0, p); 
            auto prefix_sum = [&](int num) -> long long {
                if (num == 0) {
                    return 0; 
                }
                int x = st.kth_element(num - 1); 
                return fw.sum(0, x + 1); 
            } ;
            int rk = k ? st.kth_element(k - 1) : -1; 
            long long sk = k ? prefix_sum(k) : 0; 
            long long sk1 = st.size() >= k + 1 ? prefix_sum(k + 1) : 0; 
            int rh = h && st.size() >= h ? st.kth_element(h - 1) : -1; 
            int rh1 = st.size() >= h + 1 ? st.kth_element(h) : -1; 
            REP(pos, l, r) {
                int g = ids[pos]; 
                long long cur = sumB + D[g] + 1LL * max(0, N - 2) * c; 
                int take = min(cnt - 1, k); 
                long long add = 0; 
                if (take < k) {
                    add = sum - D[g]; 
                } else if (k) {
                    add = rank[g] <= rk ? sk1 - D[g] : sk; 
                }
                cur += add - 2LL * c * take; 
                chmin(ans, cur); 
                if (N % 2 && h && take == h - 1 && st.size() - 1 >= h) {
                    long long nd = rank[g] <= rh ? ord[rh1].first : ord[rh].first; 
                    if (nd < c) {
                        chmin(ans, cur + nd - c); 
                    }
                }
            }
            l = r; 
        } 
        print(ans); 
    }
}