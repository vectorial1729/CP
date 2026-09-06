#include "library/template.hpp"
using namespace std;
using namespace vectorial;

struct Node {
    int l, r, c0, c1, bit;
};

signed main() {
    int N, K;
    read(N, K);
    vector<int> A(N);
    read(A);
    sort(ALL(A));
    if (K == 1) {
        print(0);
        return 0;
    }
    constexpr int B = 30;
    vector<int> pref((N + 1) * B);
    vector<long long> sum(N + 1);
    REP(i, N) {
        copy_n(pref.data() + i * B, B, pref.data() + (i + 1) * B);
        unsigned x = A[i];
        while (x) {
            int b = __builtin_ctz(x);
            ++pref[(i + 1) * B + b];
            x &= x - 1;
        }
        sum[i + 1] = sum[i] + A[i];
    }
    vector<Node> tr;
    tr.reserve(2 * N);
    auto build = [&](auto&& self, int l, int r) -> int {
        int v = tr.size();
        tr.push_back({l, r, -1, -1, -1});
        if (A[l] == A[r - 1]) {
            return v;
        }
        int b = 31 - __builtin_clz((unsigned)(A[l] ^ A[r - 1]));
        int base = A[l] & ~((1 << (b + 1)) - 1);
        int cut = base | (1 << b);
        int m = lower_bound(A.begin() + l, A.begin() + r, cut) - A.begin();
        tr[v].bit = b;
        tr[v].c0 = self(self, l, m);
        tr[v].c1 = self(self, m, r);

        return v;
    };
    int root = build(build, 0, N);
    auto range_xor_sum = [&](int l, int r, int x) -> long long {
        long long res = sum[r] - sum[l] + 1LL * (r - l) * x;
        long long z = 0;
        const int* pl = pref.data() + l * B;
        const int* pr = pref.data() + r * B;
        unsigned y = x;
        while (y) {
            int b = __builtin_ctz(y);
            z += 1LL * (pr[b] - pl[b]) * (1LL << b);
            y &= y - 1;
        }
        return res - 2 * z;
    };
    long long ans = 0;
    int need = K - 1;
    vector<pair<int, int>> segs;
    segs.reserve(B + 1);
    REP(i, K - 1, N) {
        int x = A[i];
        int rem = need;
        int v = root;
        segs.clear();
        while (rem and tr[v].bit != -1) {
            int b = tr[v].bit;
            int xb = x >> b & 1;
            int p = xb ? tr[v].c0 : tr[v].c1;
            int q = xb ? tr[v].c1 : tr[v].c0;
            int rr = min(tr[p].r, i);
            int cnt = max(0, rr - tr[p].l);
            if (cnt >= rem) {
                v = p;
                continue;
            }
            if (cnt) {
                segs.push_back({tr[p].l, tr[p].l + cnt});
                rem -= cnt;
            }
            v = q;
        }
        if (rem) {
            int l = tr[v].l;
            int r = min(tr[v].r, i);
            int take = min(rem, max(0, r - l));
            if (take) {
                segs.push_back({l, l + take});
                rem -= take;
            }
        }
        long long cur = 0;
        FOR(seg, segs) {
            cur += range_xor_sum(seg.first, seg.second, x);
        }
        chmax(ans, cur);
    }
    print(ans);
}