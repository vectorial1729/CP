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

#ifndef VECTORIAL_FAST_FACTORIZE
#define VECTORIAL_FAST_FACTORIZE

#include <cmath>
#include <iostream>
#include <random>
#include <numeric>
#include <utility>



#ifndef VECTORIAL_DETERMINISTIC_MILLER_RABIN
#define VECTORIAL_DETERMINISTIC_MILLER_RABIN

#include <array>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <tuple>
#include <type_traits>

#ifndef VECTORIAL_MONTGOMERY
#define VECTORIAL_MONTGOMERY

#include <cassert>
#include <cstdint>
#include <limits>

namespace vectorial {
    namespace internal::montgomery {
        template <typename Int, typename DInt>
        struct Montgomery {
        private:
            static constexpr uint32_t bits = std::numeric_limits<Int>::digits;
            static constexpr Int mask = ~Int(0);








            Int N, N2, R2;


            Int RR;
        public:
            constexpr Montgomery() = default;
            explicit constexpr Montgomery(Int N) : N(N), N2(calcN2(N)), R2(calcR2(N, N2)), RR(calcRR(N)) {
                assert(N & 1);
            }


            constexpr Int make(Int t) const {
                return reduce(static_cast<DInt>(t) * RR);
            }

            constexpr Int reduce(DInt T) const {





                DInt m = modR(static_cast<DInt>(modR(T)) * N2);






                DInt t = divR(T + m * N);






                return t >= N ? t - N : t;
            }

            constexpr Int add(Int A, Int B) const {
                return (A += B) >= N ? A - N : A;
            }
            constexpr Int sub(Int A, Int B) const {
                return (A -= B) < 0 ? A + N : A;
            }
            constexpr Int mul(Int A, Int B) const {
                return reduce(static_cast<DInt>(A) * B);
            }
            constexpr Int div(Int A, Int B) const {
                return reduce(static_cast<DInt>(A) * inv(B));
            }
            constexpr Int inv(Int A) const;

            constexpr Int pow(Int A, long long b) const {
                Int P = make(1);
                for (; b; b >>= 1) {
                    if (b & 1) P = mul(P, A);
                    A = mul(A, A);
                }
                return P;
            }

        private:
            static constexpr Int divR(DInt t) { return t >> bits; }
            static constexpr Int modR(DInt t) { return t & mask; }

            static constexpr Int calcN2(Int N) {




                DInt invN = N;
                for (uint32_t cur_bits = 2; cur_bits < bits; cur_bits *= 2) {







                    invN = modR(invN * modR(2 - N * invN));
                }
                assert(modR(N * invN) == 1);

                return modR(-invN);
            }
            static constexpr Int calcR2(Int N, Int N2) {


                return divR(1 + static_cast<DInt>(N) * N2);
            }
            static constexpr Int calcRR(Int N) {
                return -DInt(N) % N;
            }
        };
    }
    using Montgomery32 = internal::montgomery::Montgomery<uint32_t, uint64_t>;
    using Montgomery64 = internal::montgomery::Montgomery<uint64_t, __uint128_t>;
}


#endif


namespace vectorial::miller_rabin {
    namespace internal {
        constexpr uint64_t THRESHOLD_1 = 341531ULL;
        constexpr uint64_t BASE_1[]{ 9345883071009581737ULL };

        constexpr uint64_t THRESHOLD_2 = 1050535501ULL;
        constexpr uint64_t BASE_2[]{ 336781006125ULL, 9639812373923155ULL };

        constexpr uint64_t THRESHOLD_3 = 350269456337ULL;
        constexpr uint64_t BASE_3[]{ 4230279247111683200ULL, 14694767155120705706ULL, 16641139526367750375ULL };

        constexpr uint64_t THRESHOLD_4 = 55245642489451ULL;
        constexpr uint64_t BASE_4[]{ 2ULL, 141889084524735ULL, 1199124725622454117ULL, 11096072698276303650ULL };

        constexpr uint64_t THRESHOLD_5 = 7999252175582851ULL;
        constexpr uint64_t BASE_5[]{ 2ULL, 4130806001517ULL, 149795463772692060ULL, 186635894390467037ULL, 3967304179347715805ULL };

        constexpr uint64_t THRESHOLD_6 = 585226005592931977ULL;
        constexpr uint64_t BASE_6[]{ 2ULL, 123635709730000ULL, 9233062284813009ULL, 43835965440333360ULL, 761179012939631437ULL, 1263739024124850375ULL };

        constexpr uint64_t BASE_7[]{ 2U, 325U, 9375U, 28178U, 450775U, 9780504U, 1795265022U };

        template <auto BASE, std::size_t SIZE>
        constexpr bool miller_rabin(uint64_t n) {
            if (n == 2 or n == 3 or n == 5 or n == 7) return true;
            if (n <= 1 or n % 2 == 0 or n % 3 == 0 or n % 5 == 0 or n % 7 == 0) return false;
            if (n < 121) return true;

            const uint32_t s = __builtin_ctzll(n - 1);
            const uint64_t d = (n - 1) >> s;

            const Montgomery64 mg{ n };

            const uint64_t one = mg.make(1), minus_one = mg.make(n - 1);

            for (std::size_t i = 0; i < SIZE; ++i) {
                uint64_t a = BASE[i] % n;
                if (a == 0) continue;
                uint64_t Y = mg.pow(mg.make(a), d);
                if (Y == one) continue;
                for (uint32_t r = 0;; ++r, Y = mg.mul(Y, Y)) {

                    if (Y == minus_one) break;
                    if (r == s - 1) return false;
                }
            }
            return true;
        }
    }

    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    constexpr bool is_prime(T n) {
        if constexpr (std::is_signed_v<T>) {
            assert(n >= 0);
        }
        const std::make_unsigned_t<T> n_unsigned = n;
        assert(n_unsigned <= std::numeric_limits<uint64_t>::max());
        using namespace internal;
        if (n_unsigned < THRESHOLD_1) return miller_rabin<BASE_1, 1>(n_unsigned);
        if (n_unsigned < THRESHOLD_2) return miller_rabin<BASE_2, 2>(n_unsigned);
        if (n_unsigned < THRESHOLD_3) return miller_rabin<BASE_3, 3>(n_unsigned);
        if (n_unsigned < THRESHOLD_4) return miller_rabin<BASE_4, 4>(n_unsigned);
        if (n_unsigned < THRESHOLD_5) return miller_rabin<BASE_5, 5>(n_unsigned);
        if (n_unsigned < THRESHOLD_6) return miller_rabin<BASE_6, 6>(n_unsigned);
        return miller_rabin<BASE_7, 7>(n_unsigned);
    }
}

#endif

#ifndef VECTORIAL_SIEVE_OF_ERATOSTHENES
#define VECTORIAL_SIEVE_OF_ERATOSTHENES

#include <cassert>
#include <cmath>
#include <vector>

#ifndef VECTORIAL_INTERNAL_ERATOSTHENES
#define VECTORIAL_INTERNAL_ERATOSTHENES

#include <cstdint>
#include <cassert>

namespace vectorial::internal::sieve {

constexpr std::uint8_t K = 8;
constexpr std::uint8_t PROD = 2 * 3 * 5;
constexpr std::uint8_t RM[K] = { 1,  7, 11, 13, 17, 19, 23, 29 };
constexpr std::uint8_t DR[K] = { 6,  4,  2,  4,  2,  4,  6,  2 };
constexpr std::uint8_t DF[K][K] = {
    { 0, 0, 0, 0, 0, 0, 0, 1 }, { 1, 1, 1, 0, 1, 1, 1, 1 },
    { 2, 2, 0, 2, 0, 2, 2, 1 }, { 3, 1, 1, 2, 1, 1, 3, 1 },
    { 3, 3, 1, 2, 1, 3, 3, 1 }, { 4, 2, 2, 2, 2, 2, 4, 1 },
    { 5, 3, 1, 4, 1, 3, 5, 1 }, { 6, 4, 2, 4, 2, 4, 6, 1 },
};
constexpr std::uint8_t DRP[K] = { 48, 32, 16, 32, 16, 32, 48, 16 };
constexpr std::uint8_t DFP[K][K] = {
    {  0,  0,  0,  0,  0,  0,  0,  8 }, {  8,  8,  8,  0,  8,  8,  8,  8 },
    { 16, 16,  0, 16,  0, 16, 16,  8 }, { 24,  8,  8, 16,  8,  8, 24,  8 },
    { 24, 24,  8, 16,  8, 24, 24,  8 }, { 32, 16, 16, 16, 16, 16, 32,  8 },
    { 40, 24,  8, 32,  8, 24, 40,  8 }, { 48, 32, 16, 32, 16, 32, 48,  8 },
};

constexpr std::uint8_t MASK[K][K] = {
    { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 }, { 0x02, 0x20, 0x10, 0x01, 0x80, 0x08, 0x04, 0x40 },
    { 0x04, 0x10, 0x01, 0x40, 0x02, 0x80, 0x08, 0x20 }, { 0x08, 0x01, 0x40, 0x20, 0x04, 0x02, 0x80, 0x10 },
    { 0x10, 0x80, 0x02, 0x04, 0x20, 0x40, 0x01, 0x08 }, { 0x20, 0x08, 0x80, 0x02, 0x40, 0x01, 0x10, 0x04 },
    { 0x40, 0x04, 0x08, 0x80, 0x01, 0x10, 0x20, 0x02 }, { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 },
};
constexpr std::uint8_t OFFSET[K][K] = {
    { 0, 1, 2, 3, 4, 5, 6, 7, },
    { 1, 5, 4, 0, 7, 3, 2, 6, },
    { 2, 4, 0, 6, 1, 7, 3, 5, },
    { 3, 0, 6, 5, 2, 1, 7, 4, },
    { 4, 7, 1, 2, 5, 6, 0, 3, },
    { 5, 3, 7, 1, 6, 0, 4, 2, },
    { 6, 2, 3, 7, 0, 4, 5, 1, },
    { 7, 6, 5, 4, 3, 2, 1, 0, },
};

constexpr std::uint8_t mask_to_index(const std::uint8_t bits) {
    switch (bits) {
        case 1 << 0: return 0;
        case 1 << 1: return 1;
        case 1 << 2: return 2;
        case 1 << 3: return 3;
        case 1 << 4: return 4;
        case 1 << 5: return 5;
        case 1 << 6: return 6;
        case 1 << 7: return 7;
        default: assert(false);
    }
}
}

#endif


namespace vectorial {

template <unsigned int N>
class SimpleSieve {
    private:
        static constexpr unsigned int siz = N / internal::sieve::PROD + 1;
        static std::uint8_t flag[siz];
    public:
        SimpleSieve() {
            using namespace internal::sieve;
            flag[0] |= 1;
            unsigned int k_max = (unsigned int) std::sqrt(N + 2) / PROD;
            for (unsigned int kp = 0; kp <= k_max; ++kp) {
                for (std::uint8_t bits = ~flag[kp]; bits; bits &= bits - 1) {
                    const std::uint8_t mp = mask_to_index(bits & -bits), m = RM[mp];
                    unsigned int kr = kp * (PROD * kp + 2 * m) + m * m / PROD;
                    for (std::uint8_t mq = mp; kr < siz; kr += kp * DR[mq] + DF[mp][mq], ++mq &= 7) {
                        flag[kr] |= MASK[mp][mq];
                    }
                }
            }
        }
        std::vector<int> prime_list(unsigned int max_val = N) const {
            using namespace internal::sieve;
            std::vector<int> res { 2, 3, 5 };
            res.reserve(max_val / 25);
            for (unsigned int i = 0, offset = 0; i < siz and offset < max_val; ++i, offset += PROD) {
                for (uint8_t f = ~flag[i]; f;) {
                    uint8_t g = f & -f;
                    res.push_back(offset + RM[mask_to_index(g)]);
                    f ^= g;
                }
            }
            while (res.size() and (unsigned int) res.back() > max_val) res.pop_back();
            return res;
        }
        bool is_prime(const unsigned int p) const {
            using namespace internal::sieve;
            switch (p) {
                case 2: case 3: case 5: return true;
                default:
                    switch (p % PROD) {
                        case RM[0]: return ((flag[p / PROD] >> 0) & 1) == 0;
                        case RM[1]: return ((flag[p / PROD] >> 1) & 1) == 0;
                        case RM[2]: return ((flag[p / PROD] >> 2) & 1) == 0;
                        case RM[3]: return ((flag[p / PROD] >> 3) & 1) == 0;
                        case RM[4]: return ((flag[p / PROD] >> 4) & 1) == 0;
                        case RM[5]: return ((flag[p / PROD] >> 5) & 1) == 0;
                        case RM[6]: return ((flag[p / PROD] >> 6) & 1) == 0;
                        case RM[7]: return ((flag[p / PROD] >> 7) & 1) == 0;
                        default: return false;
                    }
            }
        }
};
template <unsigned int N>
std::uint8_t SimpleSieve<N>::flag[SimpleSieve<N>::siz];

template <unsigned int N>
class Sieve {
    private:
        static constexpr unsigned int base_max = (N + 1) * internal::sieve::K / internal::sieve::PROD;
        static unsigned int pf[base_max + internal::sieve::K];

    public:
        Sieve() {
            using namespace internal::sieve;
            pf[0] = 1;
            unsigned int k_max = ((unsigned int) std::sqrt(N + 1) - 1) / PROD;
            for (unsigned int kp = 0; kp <= k_max; ++kp) {
                const int base_i = kp * K, base_act_i = kp * PROD;
                for (int mp = 0; mp < K; ++mp) {
                    const int m = RM[mp], i = base_i + mp;
                    if (pf[i] == 0) {
                        unsigned int act_i = base_act_i + m;
                        unsigned int base_k = (kp * (PROD * kp + 2 * m) + m * m / PROD) * K;
                        for (std::uint8_t mq = mp; base_k <= base_max; base_k += kp * DRP[mq] + DFP[mp][mq], ++mq &= 7) {
                            pf[base_k + OFFSET[mp][mq]] = act_i;
                        }
                    }
                }
            }
        }
        bool is_prime(const unsigned int p) const {
            using namespace internal::sieve;
            switch (p) {
                case 2: case 3: case 5: return true;
                default:
                    switch (p % PROD) {
                        case RM[0]: return pf[p / PROD * K + 0] == 0;
                        case RM[1]: return pf[p / PROD * K + 1] == 0;
                        case RM[2]: return pf[p / PROD * K + 2] == 0;
                        case RM[3]: return pf[p / PROD * K + 3] == 0;
                        case RM[4]: return pf[p / PROD * K + 4] == 0;
                        case RM[5]: return pf[p / PROD * K + 5] == 0;
                        case RM[6]: return pf[p / PROD * K + 6] == 0;
                        case RM[7]: return pf[p / PROD * K + 7] == 0;
                        default: return false;
                    }
            }
        }
        int prime_factor(const unsigned int p) const {
            using namespace internal::sieve;
            switch (p % PROD) {
                case  0: case  2: case  4: case  6: case  8:
                case 10: case 12: case 14: case 16: case 18:
                case 20: case 22: case 24: case 26: case 28: return 2;
                case  3: case  9: case 15: case 21: case 27: return 3;
                case  5: case 25: return 5;
                case RM[0]: return pf[p / PROD * K + 0] ? pf[p / PROD * K + 0] : p;
                case RM[1]: return pf[p / PROD * K + 1] ? pf[p / PROD * K + 1] : p;
                case RM[2]: return pf[p / PROD * K + 2] ? pf[p / PROD * K + 2] : p;
                case RM[3]: return pf[p / PROD * K + 3] ? pf[p / PROD * K + 3] : p;
                case RM[4]: return pf[p / PROD * K + 4] ? pf[p / PROD * K + 4] : p;
                case RM[5]: return pf[p / PROD * K + 5] ? pf[p / PROD * K + 5] : p;
                case RM[6]: return pf[p / PROD * K + 6] ? pf[p / PROD * K + 6] : p;
                case RM[7]: return pf[p / PROD * K + 7] ? pf[p / PROD * K + 7] : p;
                default: assert(false);
            }
        }



        std::vector<std::pair<int, int>> factorize(unsigned int n) const {
            assert(0 < n and n <= N);
            std::vector<std::pair<int, int>> prime_powers;
            while (n > 1) {
                int p = prime_factor(n), c = 0;
                do { n /= p, ++c; } while (n % p == 0);
                prime_powers.emplace_back(p, c);
            }
            return prime_powers;
        }




        std::vector<int> divisors(unsigned int n) const {
            assert(0 < n and n <= N);
            std::vector<int> divs { 1 };
            for (auto [prime, index] : factorize(n)) {
                int sz = divs.size();
                for (int i = 0; i < sz; ++i) {
                    int d = divs[i];
                    for (int j = 0; j < index; ++j) {
                        divs.push_back(d *= prime);
                    }
                }
            }
            return divs;
        }
};
template <unsigned int N>
unsigned int Sieve<N>::pf[Sieve<N>::base_max + internal::sieve::K];
}

#endif


namespace vectorial::fast_factorize {
    namespace internal {
        template <typename T>
        constexpr int floor_log2(T n) {
            int i = 0;
            while (n) n >>= 1, ++i;
            return i - 1;
        }
        template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
        T pollard_rho(const T n) {
            using M = safely_multipliable_t<T>;
            const T m = T(1) << (floor_log2(n) / 5);

            static std::mt19937_64 rng{std::random_device{}()};
            std::uniform_int_distribution<T> dist(0, n - 1);



            while (true) {
                T c = dist(rng);
                auto f = [&](T x) -> T { return (M(x) * x + c) % n; };
                T x, y = 2, ys, q = 1, g = 1;
                for (T r = 1; g == 1; r <<= 1) {
                    x = y;
                    for (T i = 0; i < r; ++i) y = f(y);
                    for (T k = 0; k < r and g == 1; k += m) {
                        ys = y;
                        for (T i = 0; i < std::min(m, r - k); ++i) y = f(y), q = M(q) * (x > y ? x - y : y - x) % n;
                        g = std::gcd(q, n);
                    }
                }
                if (g == n) {
                    g = 1;
                    while (g == 1) ys = f(ys), g = std::gcd(x > ys ? x - ys : ys - x, n);
                }
                if (g < n) {
                    if (miller_rabin::is_prime(g)) return g;
                    if (T d = n / g; miller_rabin::is_prime(d)) return d;
                    return pollard_rho(g);
                }
            }
        }
    }

    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    std::vector<std::pair<T, int>> factorize(T n) {
        static constexpr int threshold = 1000000;
        static Sieve<threshold> sieve;

        std::vector<std::pair<T, int>> res;
        if (n <= threshold) {
            for (auto [p, q] : sieve.factorize(n)) res.emplace_back(p, q);
            return res;
        }

        if ((n & 1) == 0) {
            int q = 0;
            do ++q, n >>= 1; while ((n & 1) == 0);
            res.emplace_back(2, q);
        }
        for (T p = 3; p * p <= n; p += 2) {
            if (p >= 101 and n >= 1 << 20) {
                while (n > 1) {
                    if (miller_rabin::is_prime(n)) {
                        res.emplace_back(std::exchange(n, 1), 1);
                    } else {
                        p = internal::pollard_rho(n);
                        int q = 0;
                        do ++q, n /= p; while (n % p == 0);
                        res.emplace_back(p, q);
                    }
                }
                break;
            }
            if (n % p == 0) {
                int q = 0;
                do ++q, n /= p; while (n % p == 0);
                res.emplace_back(p, q);
            }
        }
        if (n > 1) res.emplace_back(n, 1);
        return res;
    }
}

#endif

using namespace std;
using namespace vectorial;
signed main() {
    long long N = read(); 
    auto f = fast_factorize::factorize(N); 
    int ans = 1; 
    for (auto [p, e] : f) {
        if (e >= 2) {
            ans = 0; 
        } else {
            ans = -ans; 
        }
        
    }
    print(ans); 
}