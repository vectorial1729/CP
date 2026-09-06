#include "library/template.hpp"
using namespace std;
using namespace vectorial;
using ull = unsigned long long;

struct BitSet {
    int n, m;
    vector<ull> a, tmp;

    BitSet(int n = 0) : n(n), m(n >> 6), a(m), tmp(m) {}

    bool test(int p) const {
        return a[p >> 6] >> (p & 63) & 1ULL;
    }

    void set(int p) {
        a[p >> 6] |= 1ULL << (p & 63);
    }

    void reset(int p) {
        a[p >> 6] &= ~(1ULL << (p & 63));
    }

    void shift_or(long long d) {
        d %= n;
        if (d < 0) {
            d += n;
        }
        if (d == 0) {
            return;
        }

        int q = d >> 6;
        int r = d & 63;

        if (r == 0) {
            REP(i, m) {
                int j = i + q;
                if (j >= m) {
                    j -= m;
                }
                a[j] |= tmp[i];
            }
        } else {
            REP(i, m) {
                ull x = tmp[i];
                if (!x) {
                    continue;
                }

                int j = i + q;
                if (j >= m) {
                    j -= m;
                }

                a[j] |= x << r;

                ++j;
                if (j == m) {
                    j = 0;
                }

                a[j] |= x >> (64 - r);
            }
        }
    }

    void expand(int d1, int d2) {
        if (d1 == 0 and d2 == 0) {
            return;
        }

        memcpy(tmp.data(), a.data(), sizeof(ull) * m);
        shift_or(d1);
        shift_or(d2);
    }
};

struct Machine {
    int o, a, b, c;
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, Q;
    long long X;
    read(N, X, Q);
    vector<Machine> M(N);
    int lim = 1;
    long long vmax = X;
    REP(i, N) {
        int o, a, b;
        read(o, a, b);
        chmax(lim, a);
        if (o == 0) {
            M[i] = {0, a, b, b};
            vmax += max(0, b - a);
        } else {
            int c;
            read(c);
            M[i] = {1, a, b, c};
            vmax += max({0, b - a, c - a});
        }
    }
    int mod = (int)((vmax >> 6) + 1) << 6;
    BitSet bs(mod);
    unsigned low = 0;
    int off = 0;
    if (X < lim) {
        low |= 1U << X;
    } else {
        bs.set((int)X);
    }
    auto norm = [&](long long x) {
        x %= mod;
        if (x < 0) {
            x += mod;
        }
        return (int)x;
    };
    auto add = [&](long long v, unsigned& mask) {
        if (v < lim) {
            mask |= 1U << v;
        } else {
            bs.set(norm(v - off));
        }
    };
    auto pull = [&](unsigned& mask) {
        REP(v, 1, lim) {
            int p = norm(v - off);

            if (bs.test(p)) {
                mask |= 1U << v;
                bs.reset(p);
            }
        }
    };
    FOR(e, M) {
        if (e.o == 0) {
            int d = e.b - e.a;
            unsigned old = low;
            unsigned nxt = 0;
            off = norm(off + d);
            pull(nxt);
            REP(v, 1, lim) {
                if (old >> v & 1U) {
                    if (v >= e.a) {
                        add(v + d, nxt);
                    } else {
                        add(v, nxt);
                    }
                }
            }
            low = nxt;
        } else {
            int d1 = e.b - e.a;
            int d2 = e.c - e.a;
            bs.expand(d1, d2);
            unsigned old = low;
            unsigned nxt = old;
            REP(v, e.a, lim) {
                if (old >> v & 1U) {
                    add(v + d1, nxt);
                    add(v + d2, nxt);
                }
            }
            pull(nxt);
            low = nxt;
        }
    }
    string out;
    out.reserve(2 * Q);
    LOOP(Q) {
        long long y;
        read(y);
        bool ok = false;
        if (y <= vmax) {
            if (y < lim) {
                ok = low >> y & 1U;
            } else {
                ok = bs.test(norm(y - off));
            }
        }
        out += ok ? "1\n" : "0\n";
    }
    cout << out;
}