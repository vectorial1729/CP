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

#ifndef VECTORIAL_MODINT
#define VECTORIAL_MODINT

#include <cassert>
#include <cstdint>
#include <limits>
#include <optional>
#include <iostream>

namespace vectorial {
    namespace internal::modint {
        constexpr long long safe_mod(long long x, long long m) { return (x %= m) < 0 ? x + m : x; }
        constexpr long long pow_mod(long long x, long long n, int m) {
            if (m == 1) return 0;
            unsigned int um = m;
            unsigned long long r = 1, y = safe_mod(x, m);
            for (; n; n >>= 1) {
                if (n & 1) r = (r * y) % um;
                y = (y * y) % um;
            }
            return r;
        }
        constexpr bool is_prime(int n) {
            if (n <= 1) return false;
            if (n == 2 or n == 7 or n == 61) return true;
            if (n % 2 == 0) return false;
            long long d = n - 1;
            while (d % 2 == 0) d /= 2;
            constexpr long long bases[3] = { 2, 7, 61 };
            for (long long a : bases) {
                long long t = d, y = pow_mod(a, t, n);
                for (; t != n - 1 and y != 1 and y != n - 1; t <<= 1) y = y * y % n;
                if (y != n - 1 and t % 2 == 0) return false;
            }
            return true;
        }
        constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
            a = safe_mod(a, b);
            if (a == 0) return { b, 0 };
            long long s = b, t = a, m0 = 0, m1 = 1, tmp = 0;
            while (t) {
                long long u = s / t;
                s -= t * u, m0 -= m1 * u;
                tmp = s, s = t, t = tmp;
                tmp = m0, m0 = m1, m1 = tmp;
            }
            if (m0 < 0) m0 += b / s;
            return { s, m0 };
        }

        struct barrett_K128 {
            uint32_t M;
            __uint128_t L;
            uint64_t dL, uL;
            constexpr barrett_K128(uint32_t M) : M(M), L(~__uint128_t(0) / M + 1), dL(L), uL(L >> 64) {}
            constexpr uint32_t umod() const { return M; }

            template <bool care_M1 = true>
            constexpr uint32_t rem(uint64_t c) const {
                if constexpr (care_M1) if (M == 1) return 0;

                __uint128_t cu = __uint128_t(c) * uL;
                uint64_t cd = (__uint128_t(c) * dL) >> 64;
                uint32_t r = c - uint64_t(cu >> 64) * M;
                return uint64_t(cu) > ~cd ? r - M : r;
            }

            constexpr uint32_t mul(uint32_t a, uint32_t b) const { return rem<false>(uint64_t(a) * b); }
        };
    }

    template <int m, std::enable_if_t<(1 <= m), std::nullptr_t> = nullptr>
    class static_modint {
        using mint = static_modint;

        struct raw_construct {};
        constexpr static_modint(int v, raw_construct) : _v(v) {}
    public:
        static constexpr int mod() { return m; }
        static constexpr unsigned int umod() { return m; }

        static constexpr mint raw(int v) { return mint(v, raw_construct{}); }

        constexpr static_modint() : _v(0) {}
        template <class T, std::enable_if_t<std::conjunction_v<std::is_integral<T>, std::is_signed<T>>, std::nullptr_t> = nullptr>
        constexpr static_modint(T v) : _v{} {
            int x = v % mod();
            if (x < 0) x += mod();
            _v = x;
        }
        template <class T, std::enable_if_t<std::conjunction_v<std::is_integral<T>, std::is_unsigned<T>>, std::nullptr_t> = nullptr>
        constexpr static_modint(T v) : _v(v % umod()) {}

        constexpr unsigned int val() const { return _v; }

        constexpr mint& operator++() {
            ++_v;
            if (_v == umod()) _v = 0;
            return *this;
        }
        constexpr mint& operator--() {
            if (_v == 0) _v = umod();
            --_v;
            return *this;
        }
        constexpr mint operator++(int) { mint x = *this; ++*this; return x; }
        constexpr mint operator--(int) { mint x = *this; --*this; return x; }

        constexpr mint& operator+=(const mint& rhs) {
            _v += rhs._v;
            if (_v >= umod()) _v -= umod();
            return *this;
        }
        constexpr mint& operator-=(const mint& rhs) {
            _v -= rhs._v;
            if (_v >= umod()) _v += umod();
            return *this;
        }
        constexpr mint& operator*=(const mint& rhs) {
            _v = (unsigned long long) _v * rhs._v % umod();
            return *this;
        }
        constexpr mint& operator/=(const mint& rhs) { return *this *= rhs.inv(); }

        constexpr mint operator+() const { return *this; }
        constexpr mint operator-() const { return _v == 0 ? *this : raw(umod() - _v); }

        constexpr mint pow(long long n) const {
            assert(0 <= n);
            mint x = *this, r = 1;
            for (; n; n >>= 1) {
                if (n & 1) r *= x;
                x *= x;
            }
            return r;
        }
        constexpr mint xpow(long long n) const { return n < 0 ? inv().pow(-n) : pow(n); }
        constexpr mint inv() const {
            if constexpr (is_prime_mod) {
                assert(_v);
                return pow(umod() - 2);
            } else {
                const auto [g, res] = internal::modint::inv_gcd(_v, mod());
                assert(g == 1);
                return res;
            }
        }
        friend constexpr mint operator+(const mint& lhs, const mint& rhs) { mint res = lhs; res += rhs; return res; }
        friend constexpr mint operator-(const mint& lhs, const mint& rhs) { mint res = lhs; res -= rhs; return res; }
        friend constexpr mint operator*(const mint& lhs, const mint& rhs) { mint res = lhs; res *= rhs; return res; }
        friend constexpr mint operator/(const mint& lhs, const mint& rhs) { mint res = lhs; res /= rhs; return res; }
        friend constexpr bool operator==(const mint& lhs, const mint& rhs) { return lhs._v == rhs._v; }
        friend constexpr bool operator!=(const mint& lhs, const mint& rhs) { return lhs._v != rhs._v; }
    private:
        unsigned int _v;
        static constexpr bool is_prime_mod = internal::modint::is_prime(mod());
    };

    template <int id>
    class dynamic_modint {
        using mint = dynamic_modint;
        using barrett = internal::modint::barrett_K128;

        struct raw_construct {};
        constexpr dynamic_modint(int v, raw_construct) : _v(v) {}
    public:
        static int mod() { return bt.umod(); }
        static unsigned int umod() { return bt.umod(); }

        static void set_mod(int m) {
            assert(1 <= m);
            bt = barrett(m);
        }
        static mint raw(int v) { return dynamic_modint(v, raw_construct{}); }

        dynamic_modint() : _v(0) {}
        template <class T, std::enable_if_t<std::conjunction_v<std::is_integral<T>, std::is_signed<T>>, std::nullptr_t> = nullptr>
        dynamic_modint(T v) {
            if (v < 0) {
                int x = v % mod();
                if (x < 0) x += mod();
                _v = x;
            } else _v = bt.rem(v);
        }
        template <class T, std::enable_if_t<std::conjunction_v<std::is_integral<T>, std::is_unsigned<T>>, std::nullptr_t> = nullptr>
        dynamic_modint(T v) : _v(bt.rem(v)) {}

        dynamic_modint(__uint128_t v) : _v(v % umod()) {}
        dynamic_modint(__int128_t v) {
            int x = v % mod();
            if (x < 0) x += mod();
            _v = x;
        }

        unsigned int val() const { return _v; }

        mint& operator++() {
            ++_v;
            if (_v == umod()) _v = 0;
            return *this;
        }
        mint& operator--() {
            if (_v == 0) _v = umod();
            --_v;
            return *this;
        }
        mint operator++(int) { mint x = *this; ++*this; return x; }
        mint operator--(int) { mint x = *this; --*this; return x; }

        mint& operator+=(const mint& rhs) {
            _v += rhs._v;
            if (_v >= umod()) _v -= umod();
            return *this;
        }
        mint& operator-=(const mint& rhs) {
            _v -= rhs._v;
            if (_v >= umod()) _v += umod();
            return *this;
        }
        mint& operator*=(const mint& rhs) {
            _v = bt.mul(_v, rhs._v);
            return *this;
        }
        mint& operator/=(const mint& rhs) { return *this *= rhs.inv(); }

        mint pow(long long n) const {
            assert(0 <= n);
            mint x = *this, r = 1;
            for (; n; n >>= 1) {
                if (n & 1) r *= x;
                x *= x;
            }
            return r;
        }
        mint xpow(long long n) const { return n < 0 ? inv().pow(-n) : pow(n); }
        mint inv() const {
            const auto [g, res] = internal::modint::inv_gcd(_v, mod());
            assert(g == 1);
            return res;
        }

        friend mint operator+(const mint& lhs, const mint& rhs) { mint res = lhs; res += rhs; return res; }
        friend mint operator-(const mint& lhs, const mint& rhs) { mint res = lhs; res -= rhs; return res; }
        friend mint operator*(const mint& lhs, const mint& rhs) { mint res = lhs; res *= rhs; return res; }
        friend mint operator/(const mint& lhs, const mint& rhs) { mint res = lhs; res /= rhs; return res; }
        friend bool operator==(const mint& lhs, const mint& rhs) { return lhs._v == rhs._v; }
        friend bool operator!=(const mint& lhs, const mint& rhs) { return lhs._v != rhs._v; }
    private:
        unsigned int _v;
        static inline barrett bt{ 998244353 };
    };

    using modint998244353 = static_modint<998244353>;
    using modint1000000007 = static_modint<1000000007>;
    using modint = dynamic_modint<-1>;

    template <typename T> struct is_modint : std::false_type {};
    template <int m> struct is_modint<static_modint<m>> : std::true_type {};
    template <int id> struct is_modint<dynamic_modint<id>> : std::true_type {};
    template <typename T> constexpr bool is_modint_v = is_modint<T>::value;

    template <typename T> struct is_static_modint : std::false_type {};
    template <int m> struct is_static_modint<static_modint<m>> : std::true_type {};
    template <typename T> constexpr bool is_static_modint_v = is_static_modint<T>::value;

    template <typename T> struct is_dynamic_modint : std::false_type {};
    template <int id> struct is_dynamic_modint<dynamic_modint<id>> : std::true_type {};
    template <typename T> constexpr bool is_dynamic_modint_v = is_dynamic_modint<T>::value;

    template <typename mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t> = nullptr>
    std::optional<mint> mod_sqrt(mint a) {
        const int p = mint::mod();
        if (a == 0) return mint(0);
        if (p == 2) return a;
        if (a.pow((p - 1) / 2) != 1) return std::nullopt;
        mint b = 1;
        while (b.pow((p - 1) / 2) == 1) ++b;
        const int tlz = __builtin_ctz(p - 1), q = (p - 1) >> tlz;
        mint x = a.pow((q + 1) / 2);
        b = b.pow(q);
        for (int shift = 2; x * x != a; ++shift) {
            mint e = a.inv() * x * x;
            if (e.pow(1 << (tlz - shift)) != 1) x *= b;
            b *= b;
        }
        return x;
    }

    template <typename mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t> = nullptr>
    mint sqrt(mint a) { return *mod_sqrt(a); }
    template <typename mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t> = nullptr>
    mint log(mint a) { assert(a == 1); return 0; }
    template <typename mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t> = nullptr>
    mint exp(mint a) { assert(a == 0); return 1; }
    template <typename mint, typename T, std::enable_if_t<is_modint_v<mint>, std::nullptr_t> = nullptr>
    mint pow(mint a, T b) { return a.xpow(b); }
    template <typename mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t> = nullptr>
    mint inv(mint a) { return a.inv(); }

    template <typename mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t> = nullptr>
    std::istream& operator>>(std::istream& is, mint& v) { long long val; is >> val, v = val; return is; }
    template <typename mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t> = nullptr>
    std::ostream& operator<<(std::ostream& os, const mint& v) { return os << v.val(); }
}

#endif

using namespace std;
using namespace vectorial;
using mint = modint998244353; 
int main() {
    int T;
    read(T); 
    LOOP(T) {
       int N = read(); 
       vector<long long> A(N), B(N); 
       read(A, B); 
       vector<vector<int>> G(N); 
       REP(i, N - 1) {
        int u, v; 
        read(u, v); 
         --u, --v; 
         G[u].push_back(v); 
         G[v].push_back(u); 
       } 
       vector<int> par(N, -1), ord; 
       ord.reserve(N); 
       ord.push_back(0); 
       REP(i, N) {
        int v = ord[i]; 
        for (int u : G[v]) {
            if (u == par[v]) {
                continue; 
            }
            par[u] = v; 
            ord.push_back(u); 
        }
       }
       vector<long long> sa = A, sb = B, dp(N); 
       RREP(ii, N) {
        int v = ord[ii]; 
        vector<int> ch; 
        for (int u : G[v]) {
            if (par[u] == v) {
                ch.push_back(u); 
            }
        }
        sort(ch.begin(), ch.end(), [&](int x, int y) {return sa[x] * sb[y] < sa[y] * sb[x]; }); 
        long long cur = A[v]; 
        long long res = 0; 
        for (int u : ch) {
            res += dp[u]; 
            res += sb[u] * (cur + sa[u]); 
            cur += sa[u]; 
            sa[v] += sa[u]; 
            sb[v] += sb[u]; 
        }
        dp[v] = res; 
       }
       print(dp[0]); 
    }
}