#if __has_include(<bits/stdc++.h>)
#include <bits/stdc++.h>
#else
#include <algorithm>
#include <array>
#include <cstddef>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <queue>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#endif
namespace vectorial {
    template <class T> bool chmin(T& x, const T& y) { return y >= x ? false : (x = y, true); }
    template <class T> bool chmax(T& x, const T& y) { return y <= x ? false : (x = y, true); }
    template <class T> constexpr int pow_m1(T n) { return -(n & 1) | 1; }
    template <class T> constexpr T fld(const T x, const T y) { T q = x / y, r = x % y; return q - ((x ^ y) < 0 and (r != 0)); }
    template <class T> constexpr T cld(const T x, const T y) { T q = x / y, r = x % y; return q + ((x ^ y) > 0 and (r != 0)); }
}
namespace vectorial::macro {
#define IMPL_REPITER(cond) auto& begin() { return *this; } auto end() { return nullptr; } auto& operator*() { return _val; } auto& operator++() { return _val += _step, *this; } bool operator!=(std::nullptr_t) { return cond; }
    template <class Int, class IntL = Int, class IntStep = Int, std::enable_if_t<(std::is_signed_v<Int> == std::is_signed_v<IntL>), std::nullptr_t> = nullptr> struct rep_impl {
        Int _val; const Int _end, _step;
        rep_impl(Int n) : rep_impl(0, n) {}
        rep_impl(IntL l, Int r, IntStep step = 1) : _val(l), _end(r), _step(step) {}
        IMPL_REPITER((_val < _end))
    };
    template <class Int, class IntL = Int, class IntStep = Int, std::enable_if_t<(std::is_signed_v<Int> == std::is_signed_v<IntL>), std::nullptr_t> = nullptr> struct rrep_impl {
        Int _val; const Int _end, _step;
        rrep_impl(Int n) : rrep_impl(0, n) {}
        rrep_impl(IntL l, Int r) : _val(r - 1), _end(l), _step(-1) {}
        rrep_impl(IntL l, Int r, IntStep step) : _val(l + fld<Int>(r - l - 1, step) * step), _end(l), _step(-step) {}
        IMPL_REPITER((_val >= _end))
    };
    template <class Int, class IntStep = Int> struct repinf_impl {
        Int _val; const Int _step;
        repinf_impl(Int l, IntStep step = 1) : _val(l), _step(step) {}
        IMPL_REPITER((true))
    };
#undef IMPL_REPITER
}
#ifndef VECTORIAL_INPUT_STREAM
#define VECTORIAL_INPUT_STREAM

#include <iostream>
#ifndef VECTORIAL_TYPE_TRITS
#define VECTORIAL_TYPE_TRITS

#include <limits>
#include <iostream>
#include <type_traits>

namespace vectorial {
    template <typename ...Constraints> using constraints_t = std::enable_if_t<std::conjunction_v<Constraints...>, std::nullptr_t>;

    template <typename T, typename = std::nullptr_t> struct bitnum { static constexpr int value = 0; };
    template <typename T> struct bitnum<T, constraints_t<std::is_integral<T>>> { static constexpr int value = std::numeric_limits<std::make_unsigned_t<T>>::digits; };
    template <typename T> static constexpr int bitnum_v = bitnum<T>::value;
    template <typename T, size_t n> struct is_nbit { static constexpr bool value = bitnum_v<T> == n; };
    template <typename T, size_t n> static constexpr bool is_nbit_v = is_nbit<T, n>::value;

    template <typename T, typename = std::nullptr_t> struct safely_multipliable { using type = T; };
    template <typename T> struct safely_multipliable<T, constraints_t<std::is_signed<T>, is_nbit<T, 32>>> { using type = long long; };
    template <typename T> struct safely_multipliable<T, constraints_t<std::is_signed<T>, is_nbit<T, 64>>> { using type = __int128_t; };
    template <typename T> struct safely_multipliable<T, constraints_t<std::is_unsigned<T>, is_nbit<T, 32>>> { using type = unsigned long long; };
    template <typename T> struct safely_multipliable<T, constraints_t<std::is_unsigned<T>, is_nbit<T, 64>>> { using type = __uint128_t; };
    template <typename T> using safely_multipliable_t = typename safely_multipliable<T>::type;

    template <typename T, typename = void> struct rec_value_type { using type = T; };
    template <typename T> struct rec_value_type<T, std::void_t<typename T::value_type>> {
        using type = typename rec_value_type<typename T::value_type>::type;
    };
    template <typename T> using rec_value_type_t = typename rec_value_type<T>::type;

    template <typename T> class is_iterable {
        template <typename T_> static auto test(T_ e) -> decltype(e.begin(), e.end(), std::true_type{});
        static std::false_type test(...);
    public:
        static constexpr bool value = decltype(test(std::declval<T>()))::value;
    };
    template <typename T> static constexpr bool is_iterable_v = is_iterable<T>::value;
    template <typename T> class is_writable {
        template <typename T_> static auto test(T_ e) -> decltype(std::declval<std::ostream&>() << e, std::true_type{});
        static std::false_type test(...);
    public:
        static constexpr bool value = decltype(test(std::declval<T>()))::value;
    };
    template <typename T> static constexpr bool is_writable_v = is_writable<T>::value;
    template <typename T> class is_readable {
        template <typename T_> static auto test(T_ e) -> decltype(std::declval<std::istream&>() >> e, std::true_type{});
        static std::false_type test(...);
    public:
        static constexpr bool value = decltype(test(std::declval<T>()))::value;
    };
    template <typename T> static constexpr bool is_readable_v = is_readable<T>::value;
}
#endif
namespace vectorial::io {
    template <typename IStream, std::enable_if_t<std::conjunction_v<std::is_base_of<std::istream, std::remove_reference_t<IStream>>, std::negation<std::is_const<std::remove_reference_t<IStream>>>>, std::nullptr_t> = nullptr>
    struct InputStream {
    private:
        using istream_type = std::remove_reference_t<IStream>;
        IStream is;
        struct { InputStream* is; template <typename T> operator T() { T e; *is >> e; return e; } } _reader{ this };
    public:
        template <typename IStream_> InputStream(IStream_ &&is) : is(std::move(is)) {}
        template <typename IStream_> InputStream(IStream_ &is) : is(is) {}
        template <typename T> InputStream& operator>>(T& e) {
            if constexpr (vectorial::is_readable_v<T>) is >> e; else _read(e);
            return *this;
        }
        auto read() { return _reader; }
        template <typename Head, typename... Tail>
        void read(Head& head, Tail &...tails) { ((*this >> head) >> ... >> tails); }
        istream_type& get_stream() { return is; }
    private:
        static __uint128_t _stou128(const std::string& s) {
            __uint128_t ret = 0;
            for (char c : s) if ('0' <= c and c <= '9') ret = 10 * ret + c - '0';
            return ret;
        }
        static __int128_t _stoi128(const std::string& s) { return (s[0] == '-' ? -1 : +1) * _stou128(s); }

        void _read(__uint128_t& v) { v = _stou128(std::string(_reader)); }
        void _read(__int128_t& v) { v = _stoi128(std::string(_reader)); }
        template <typename T, typename U>
        void _read(std::pair<T, U>& a) { *this >> a.first >> a.second; }
        template <size_t N = 0, typename ...Args>
        void _read(std::tuple<Args...>& a) { if constexpr (N < sizeof...(Args)) *this >> std::get<N>(a), _read<N + 1>(a); }
        template <typename Iterable, std::enable_if_t<vectorial::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
        void _read(Iterable& a) { for (auto& e : a) *this >> e; }
    };
    template <typename IStream>
    InputStream(IStream &&) -> InputStream<IStream>;
    template <typename IStream>
    InputStream(IStream &) -> InputStream<IStream&>;

    InputStream cin{ std::cin };

    auto read() { return cin.read(); }
    template <typename Head, typename... Tail>
    void read(Head& head, Tail &...tails) { cin.read(head, tails...); }
}
namespace vectorial { using io::read; }
#endif

#ifndef VECTORIAL_OUTPUT_STREAM
#define VECTORIAL_OUTPUT_STREAM

#include <iostream>

namespace vectorial::io {
    template <typename OStream, std::enable_if_t<std::conjunction_v<std::is_base_of<std::ostream, std::remove_reference_t<OStream>>, std::negation<std::is_const<std::remove_reference_t<OStream>>>>, std::nullptr_t> = nullptr>
    struct OutputStream {
    private:
        using ostream_type = std::remove_reference_t<OStream>;
        OStream os;
    public:
        template <typename OStream_> OutputStream(OStream_ &&os) : os(std::move(os)) {}
        template <typename OStream_> OutputStream(OStream_ &os) : os(os) {}
        template <typename T> OutputStream& operator<<(const T& e) {
            if constexpr (vectorial::is_writable_v<T>) os << e; else _print(e);
            return *this;
        }
        void print() { *this << '\n'; }
        template <typename Head, typename... Tail>
        void print(const Head& head, const Tail &...tails) { *this << head, ((*this << ' ' << tails), ...), *this << '\n'; }
        template <typename Iterable, std::enable_if_t<vectorial::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
        void print_all(const Iterable& v, std::string sep = " ", std::string end = "\n") {
            for (auto it = v.begin(); it != v.end();) if (*this << *it; ++it != v.end()) *this << sep;
            *this << end;
        }
        ostream_type& get_stream() { return os; }
    private:
        void _print(__uint128_t value) {
            char buffer[41], *d = std::end(buffer);
            do *--d = '0' + (value % 10), value /= 10; while (value);
            os.rdbuf()->sputn(d, std::end(buffer) - d);
        }
        void _print(__int128_t value) {
            if (value < 0) *this << '-';
            _print(__uint128_t(value < 0 ? -value : value));
        }
        template <typename T, typename U>
        void _print(const std::pair<T, U>& a) { *this << a.first << ' ' << a.second; }
        template <size_t N = 0, typename ...Args>
        void _print(const std::tuple<Args...>& a) {
            if constexpr (N < std::tuple_size_v<std::tuple<Args...>>) {
                if constexpr (N) *this << ' ';
                *this << std::get<N>(a), _print<N + 1>(a);
            }
        }
        template <typename Iterable, std::enable_if_t<vectorial::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
        void _print(const Iterable& a) { print_all(a, " ", ""); }
    };
    template <typename OStream_>
    OutputStream(OStream_ &&) -> OutputStream<OStream_>;
    template <typename OStream_>
    OutputStream(OStream_ &) -> OutputStream<OStream_&>;

    OutputStream cout{ std::cout }, cerr{ std::cerr };

    template <typename... Args>
    void print(const Args &... args) { cout.print(args...); }
    template <typename Iterable, std::enable_if_t<vectorial::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
    void print_all(const Iterable& v, const std::string& sep = " ", const std::string& end = "\n") { cout.print_all(v, sep, end); }
}
namespace vectorial { using io::print, io::print_all; }
#endif


namespace vectorial {
    template <class T, class ToKey, class CompKey = std::less<>, std::enable_if_t<std::conjunction_v<std::is_invocable<ToKey, T>, std::is_invocable_r<bool, CompKey, std::invoke_result_t<ToKey, T>, std::invoke_result_t<ToKey, T>>>, std::nullptr_t> = nullptr>
    auto comparator(const ToKey& to_key, const CompKey& comp_key = std::less<>()) {
        return [=](const T& x, const T& y) { return comp_key(to_key(x), to_key(y)); };
    }
    template <class Compare, std::enable_if_t<std::is_invocable_r_v<bool, Compare, int, int>, std::nullptr_t> = nullptr>
    std::vector<int> sorted_indices(int n, const Compare& compare) {
        std::vector<int> p(n);
        return std::iota(p.begin(), p.end(), 0), std::sort(p.begin(), p.end(), compare), p;
    }
    template <class ToKey, std::enable_if_t<std::is_invocable_v<ToKey, int>, std::nullptr_t> = nullptr>
    std::vector<int> sorted_indices(int n, const ToKey& to_key) { return sorted_indices(n, comparator<int>(to_key)); }
    template <class T, class Comparator>
    auto priority_queue_with_comparator(const Comparator& comparator) { return std::priority_queue<T, std::vector<T>, Comparator>{ comparator }; }
    template <class Iterable, std::enable_if_t<vectorial::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
    void sort_unique_erase(Iterable& a) { std::sort(a.begin(), a.end()), a.erase(std::unique(a.begin(), a.end()), a.end()); }

    template <size_t D> struct Dim : std::array<int, D> {
        template <typename ...Ints> Dim(const Ints& ...ns) : std::array<int, D>::array{ static_cast<int>(ns)... } {}
    };
    template <typename ...Ints> Dim(const Ints& ...) -> Dim<sizeof...(Ints)>;
    template <class T, size_t D, size_t I = 0>
    auto ndvec(const Dim<D> &ns, const T& value = {}) {
        if constexpr (I + 1 < D) {
            return std::vector(ns[I], ndvec<T, D, I + 1>(ns, value));
        } else {
            return std::vector<T>(ns[I], value);
        }
    }
}
namespace vectorial {
    using int128 = __int128_t;
    using uint128 = __uint128_t;
    template <class T> using min_priority_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;
    template <class T> using max_priority_queue = std::priority_queue<T, std::vector<T>, std::less<T>>;
}
namespace vectorial { const std::string Yes = "Yes", No = "No", YES = "YES", NO = "NO"; }

#ifdef LOCAL
#  define debug(...) debug_impl(#__VA_ARGS__, __VA_ARGS__)
template <class H, class... Ts> void debug_impl(const char* s, const H& h, const Ts&... t) {
    vectorial::io::cerr << "[\033[32mDEBUG\033[m] " << s << ": " << h, ((vectorial::io::cerr << ", " << t), ..., (vectorial::io::cerr << "\n"));
}
#else
#  define debug(...) void(0)
#endif
#define FOR(e, v) for (auto &&e : v)
#define CFOR(e, v) for (const auto &e : v)
#define REP(i, ...) CFOR(i, vectorial::macro::rep_impl(__VA_ARGS__))
#define RREP(i, ...) CFOR(i, vectorial::macro::rrep_impl(__VA_ARGS__))
#define REPINF(i, ...) CFOR(i, vectorial::macro::repinf_impl(__VA_ARGS__))
#define LOOP(n) for ([[maybe_unused]] const auto& _ : vectorial::macro::rep_impl(n))
#define ALL(iterable) std::begin(iterable), std::end(iterable)

#ifndef VECTORIAL_MAXIMUM_RECTANGLE
#define VECTORIAL_MAXIMUM_RECTANGLE

#include <tuple>
#include <vector>

namespace vectorial {

    template <typename Histogram, typename Func>
    void maximal_rectangles_hist(const Histogram& h, Func &&f) {
        using Value = std::decay_t<decltype(h[0])>;

        static_assert((std::is_invocable_v<Func, int, int, Value>));

        const int n = h.size();
        std::vector<std::pair<int, Value>> stack;
        for (int r = 0; r <= n; ++r) {
            Value hr = r < n ? h[r] : 0;
            int j = r;
            while (stack.size()) {
                auto [l, hl] = stack.back();
                if (hl < hr) break;
                f(l, r, hl);
                stack.pop_back();
                j = l;
            }
            stack.emplace_back(j, hr);
        }
    }


    template <typename Grid, typename Func>
    void maximal_rectangles(const Grid& g, Func &&f) {
        static_assert((std::is_invocable_v<Func, int, int, int, int>));
        const int n = g.size();
        if (n == 0) return;
        const int m = g[0].size();
        std::vector<int> h(m), cnt_zero(m + 1);
        for (int i = 0; i < n; ++i) {
            for (int r = 0; r < m; ++r) {
                h[r] = g[i][r] ? h[r] + 1 : 0;
                cnt_zero[r + 1] = cnt_zero[r] + (i + 1 != n ? not bool(g[i + 1][r]) : 1);
            }
            maximal_rectangles_hist(h, [i, &f, &cnt_zero](int l, int r, int h) {
                if (cnt_zero[r] - cnt_zero[l]) {
                    f(i - h + 1, i + 1, l, r);
                }
            });
        }
    }


    template <typename Grid>
    std::pair<int, std::tuple<int, int, int, int>> maximum_rectngle(const Grid& g) {
        int max_area = 0;
        std::tuple<int, int, int, int> max_rect;

        maximal_rectangles(g, [&max_area, &max_rect](int u, int d, int l, int r){
            int area = (d - u) * (r - l);
            if (area > max_area) {
                max_area = area;
                max_rect = { u, d, l, r };
            }
        });

        return { max_area, max_rect };
    }
}


#endif

#ifndef VECTORIAL_CARTESIAN_TREE
#define VECTORIAL_CARTESIAN_TREE

#include <array>
#include <cassert>
#include <functional>
#include <vector>

namespace vectorial {
    struct CartesianTree : public std::vector<std::array<int, 2>> {
        using base_type = std::vector<std::array<int, 2>>;

        static constexpr int absent = -1;

        const int root;

        CartesianTree() : base_type(), root(0) {}
        CartesianTree(int root, const base_type& g) : base_type(g), root(root) {}
        CartesianTree(int root, base_type&& g) : base_type(std::move(g)), root(root) {}

        auto ranges() const {
            std::vector<std::pair<int, int>> res;
            res.reserve(size());
            auto rec = [&](auto rec, int l, int m, int r) -> void {
                if (m == absent) return;
                const auto& [lm, rm] = (*this)[m];
                rec(rec, l, lm, m), res.emplace_back(l, r), rec(rec, m + 1, rm, r);
            };
            rec(rec, 0, root, size());
            return res;
        }
    };

    template <typename Comparator>
    struct CartesianTreeBuilder {
        CartesianTreeBuilder() = default;
        template <typename RandomAccessibleContainer>
        CartesianTreeBuilder(const RandomAccessibleContainer& a, Comparator comp = Comparator{}) : n(a.size()), comp(comp), par(calc_par(a, comp)) {}

        CartesianTree build() const {
            int root = -1;
            std::vector<std::array<int, 2>> g(n, { CartesianTree::absent, CartesianTree::absent });
            for (int i = 0; i < n; ++i) {
                int p = par[i];
                (p >= 0 ? g[p][p <= i] : root) = i;
            }
            return CartesianTree{ root, std::move(g) };
        }

        template <typename RandomAccessibleContainer>
        static CartesianTree build(const RandomAccessibleContainer& a, Comparator comp = Comparator{}) {
            return CartesianTreeBuilder(a, comp).build();
        }

        int parent(std::size_t i) const {
            assert(i < std::size_t(n));
            return par[i];
        }
        int operator[](std::size_t i) const {
            return parent(i);
        }
    private:
        const int n;
        const Comparator comp;
        const std::vector<int> par;

        template <typename RandomAccessibleContainer>
        static std::vector<int> calc_par(const RandomAccessibleContainer& a, Comparator comp) {
            const int n = a.size();
            std::vector<int> par(n, -1);
            for (int i = 1; i < n; ++i) {
                int p = i - 1, l = i;
                while (p >= 0 and comp(a[i], a[p])) l = p, p = par[p];
                par[l] = i, par[i] = p;
            }
            return par;
        }
    };

    using MinCartesianTreeBuilder = CartesianTreeBuilder<std::less<>>;
    using MaxCartesianTreeBuilder = CartesianTreeBuilder<std::greater<>>;
}

#endif

#ifndef VECTORIAL_LI_CHAO_SEGTREE
#define VECTORIAL_LI_CHAO_SEGTREE

#include <algorithm>
#include <cassert>
#include <optional>
#include <vector>

namespace vectorial {
    template <typename T, bool is_min_query = true>
    class LiChaoSegmentTree {
        struct Line {
            T a, b;
            Line() : a(T(0)), b(std::numeric_limits<T>::max()) {}
            Line(T a, T b) : a(a), b(b) {}
            bool operator==(const Line& other) const {
                return a == other.a and b == other.b;
            }
            T operator()(T x) const {
                return *this == Line{} ? std::numeric_limits<T>::max() : a * x + b;
            }
            Line operator-() const { return Line{ -a, -b }; }
        };

    public:
        LiChaoSegmentTree() : LiChaoSegmentTree(std::vector<T>{}) {}


        LiChaoSegmentTree(const std::vector<T>& query_coordinates) : pos(query_coordinates) {
            std::sort(pos.begin(), pos.end());
            pos.erase(std::unique(pos.begin(), pos.end()), pos.end());
            n = pos.size();
            m = ceil_pow2(n);
            log_m = floor_log2(m);
            pos.resize(m, pos.size() ? pos.back() : T(0));
            seg.resize(2 * m, Line{});
        }


        void add_segment(T min_x, T max_x, T a, T b) {
            Line f{ a, b };
            if constexpr (not is_min_query) f = -f;

            int l = std::lower_bound(pos.begin(), pos.end(), min_x) - pos.begin();
            int r = std::upper_bound(pos.begin(), pos.end(), max_x) - pos.begin();
            if (r == n) r = m;
            for (l += m, r += m; l < r; l >>= 1, r >>= 1) {
                if (l & 1) add_segment(l++, f);
                if (r & 1) add_segment(--r, f);
            }
        }


        void add_line(T a, T b) {
            add_segment(std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), a, b);
        }







        std::optional<T> operator()(T x) const {
            int p = std::lower_bound(pos.begin(), pos.end(), x) - pos.begin();
            assert(pos[p] == x);
            T res = std::numeric_limits<T>::max();
            bool none = true;
            for (p += m; p; p >>= 1) {
                none &= seg[p] == Line{};
                res = std::min(res, seg[p](x));
            }
            if (none) return std::nullopt;
            if constexpr (is_min_query) {
                return std::make_optional(res);
            } else {
                return std::make_optional(-res);
            }
        }







        std::optional<T> query(T x) const {
            return (*this)(x);
        }

    private:
        std::vector<T> pos;
        int n, m, log_m;
        std::vector<Line> seg;

        static int ceil_pow2(int n) {
            int k = 1;
            while (k < n) k <<= 1;
            return k;
        }
        static int floor_log2(int n) {
            return 31 - __builtin_clz(n);
        }

        std::pair<int, int> get_index_range(int k) {
            int log_w = log_m - floor_log2(k), w = 1 << log_w;
            int l = (k << log_w) - m;
            return { l, l + w };
        }

        void add_segment(int k, Line f) {
            auto [l, r] = get_index_range(k);
            for (int w = r - l; w;) {
                Line& g = seg[k];
                const T xl = pos[l], xm = pos[(l + r) >> 1], xr = pos[r - 1];
                T fl = f(xl), fm = f(xm), fr = f(xr);
                T gl = g(xl), gm = g(xm), gr = g(xr);
                if (fm < gm) std::swap(f, g), std::swap(fl, gl), std::swap(fm, gm), std::swap(fr, gr);
                k <<= 1, w >>= 1;
                if (fl < gl) {
                    k |= 0, r -= w;
                } else if (fr < gr) {
                    k |= 1, l += w;
                } else {
                    break;
                }
            }
        }
    };
}


#endif

#ifndef VECTORIAL_COM_DUAL_SEGTREE
#define VECTORIAL_COM_DUAL_SEGTREE

#include <cassert>
#include <vector>

namespace vectorial {
    template <typename T, typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>
    struct CommutativeDualSegmentTree {
        CommutativeDualSegmentTree() = default;
        CommutativeDualSegmentTree(std::vector<T>&& a) : n(a.size()), m(ceil_pow2(a.size())), data(std::move(a)), lazy(m, id()) {}
        CommutativeDualSegmentTree(const std::vector<T>& a) : CommutativeDualSegmentTree(std::vector<T>(a)) {}
        CommutativeDualSegmentTree(int n, const T& fill_value) : CommutativeDualSegmentTree(std::vector<T>(n, fill_value)) {}

        T operator[](int i) const {
            assert(0 <= i and i < n);
            T res = data[i];
            for (i = (i + m) >> 1; i; i >>= 1) res = mapping(lazy[i], res);
            return res;
        }
        T get(int i) const {
            return (*this)[i];
        }
        void apply(int l, int r, const F& f) {
            assert(0 <= l and r <= n);
            for (l += m, r += m; l < r; l >>= 1, r >>= 1) {
                if (l & 1) apply(l++, f);
                if (r & 1) apply(--r, f);
            }
        }
    protected:
        int n, m;
        std::vector<T> data;
        std::vector<F> lazy;

        void apply(int k, const F& f) {
            if (k < m) {
                lazy[k] = composition(f, lazy[k]);
            } else if (k - m < n) {
                data[k - m] = mapping(f, data[k - m]);
            }
        }
    private:
        static int ceil_pow2(int n) {
            int m = 1;
            while (m < n) m <<= 1;
            return m;
        }
    };
}

#endif

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