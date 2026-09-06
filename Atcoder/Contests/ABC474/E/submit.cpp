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

#ifndef VECTORIAL_FENWICK_TREE
#define VECTORIAL_FENWICK_TREE

#include <vector>
#include <map>
#include <unordered_map>

namespace vectorial {
    namespace internal {
        template <typename T, typename index_t = int, typename Container = std::vector<T>>
        class FenwickTreeBase {
        public:
            FenwickTreeBase() = default;
            explicit FenwickTreeBase(index_t n) : n(n) {}

            int size() const {
                return n;
            }
            void add(index_t i, T v) {
                for (++i; i <= n; i += (i & -i)) data[i - 1] += v;
            }
            T sum(index_t l, index_t r) const {
                return sum(r) - sum(l);
            }
            auto operator[](int i) {
                struct {
                    int i;
                    FenwickTreeBase& ft;
                    operator T() const { return ft.sum(i, i + 1); }
                    auto& operator++() { return *this += 1; }
                    auto& operator--() { return *this -= 1; }
                    auto& operator+=(T val) { ft.add(i, val); return *this; }
                    auto& operator-=(T val) { ft.add(i, -val); return *this; }
                    auto& operator*=(T val) { T cur = ft.sum(i, i + 1); ft.add(i, cur * val - cur); return *this; }
                    auto& operator/=(T val) { T cur = ft.sum(i, i + 1); ft.add(i, cur / val - cur); return *this; }
                    auto& operator%=(T val) { T cur = ft.sum(i, i + 1); ft.add(i, cur % val - cur); return *this; }
                    auto& operator =(T val) { T cur = ft.sum(i, i + 1); ft.add(i, val - cur); return *this; }
                } obj{ i, *this };
                return obj;
            }
            T operator()(int l, int r) const { return sum(l, r); }

            Container& get_internal_container() { return data; }
        protected:
            index_t n;
            Container data;
            template <typename ...Args>
            FenwickTreeBase(index_t n, Args &&...args) : n(n), data(std::forward<Args>(args)...) {}
        private:
            T sum(int r) const {
                T s{};
                for (; r; r -= r & -r) s += data[r - 1];
                return s;
            }
        };

        template <typename Key, typename Value, bool unordered>
        using cond_map_t = std::conditional_t<unordered, std::unordered_map<Key, Value>, std::map<Key, Value>>;

    }

    template <typename T>
    struct FenwickTree : public internal::FenwickTreeBase<T> {
        FenwickTree() : FenwickTree(0) {}
        explicit FenwickTree(int n) : internal::FenwickTreeBase<T>::FenwickTreeBase(n, n, T{}) {}
        explicit FenwickTree(std::vector<T>&& a) : internal::FenwickTreeBase<T>::FenwickTreeBase(a.size(), std::move(a)) {
            for (int i = 1; i <= this->n; ++i) {
                int p = i + (i & -i);
                if (p <= this->n) this->data[p - 1] += this->data[i - 1];
            }
        }
        explicit FenwickTree(const std::vector<T>& a) : FenwickTree(std::vector<T>(a)) {}
    };

    template <typename T, typename index_t, bool use_unordered_map = false>
    using MapFenwickTree = internal::FenwickTreeBase<T, index_t, internal::cond_map_t<index_t, T, use_unordered_map>>;

}

#endif

#ifndef VECTORIAL_FENWICK_TREE_SET
#define VECTORIAL_FENWICK_TREE_SET

#include <array>
#include <cassert>
#include <cstdint>
#include <numeric>
#include <vector>

#ifdef _MSC_VER
#  include <intrin.h>
#else
#  include <x86intrin.h>
#endif

namespace vectorial {
    struct fenwick_tree_set {
    private:
        template <typename T>
        struct is_container {
            template <typename T2>
            static auto test(T2 t) -> decltype(++t.begin() != t.end(), *t.begin(), std::true_type{});
            static std::false_type test(...);
        public:
            static constexpr bool value = decltype(test(std::declval<T>()))::value;
        };
        static constexpr int WORD = 64, MASK_WORD = 63, LOG_WORD = 6;
        static constexpr int SEARCH_WIDTH = 1;
    public:
        fenwick_tree_set() : fenwick_tree_set(0) {}

        explicit fenwick_tree_set(int n, bool fullset = false): _n(n), _wn(std::max((_n + (WORD - 1)) >> LOG_WORD, 1)), _lg(top_setbit(_wn)), _siz(0), _d(_wn + 1), _bs(_wn) {
            if (fullset) {
                std::vector<int> values(n);
                std::iota(values.begin(), values.end(), 0);
                construct_from_values(values);
            }
        }

        template <typename Container, std::enable_if_t<is_container<Container>::value, std::nullptr_t> = nullptr>
        fenwick_tree_set(int n, const Container &values): fenwick_tree_set(n) {
            construct_from_values(values);
        }

        template <typename Container, std::enable_if_t<is_container<Container>::value, std::nullptr_t> = nullptr>
        fenwick_tree_set(const Container &seq01, typename Container::value_type one = 1): fenwick_tree_set(seq01.size()) {
            std::vector<int> values;
            for (int i = 0; i < _n; ++i) if (seq01[i] == one) values.push_back(i);
            construct_from_values(values);
        }



        int size() const { return _siz; }



        bool contains(int v) const {
            if (not (0 <= v and v < _n)) return false;
            const auto [t, u] = index(v);
            return (_bs[t] >> u) & 1;
        }



        bool insert(int v) {
            if (contains(v)) return false;
            add<+1>(v);
            const auto [t, u] = index(v);
            _bs[t] |= uint64_t(1) << u;
            return true;
        }



        bool erase(int v) {
            if (not contains(v)) return false;
            add<-1>(v);
            const auto [t, u] = index(v);
            _bs[t] &= ~(uint64_t(1) << u);
            return true;
        }



        int count_lt(int v) const {
            if (v <= 0) return 0;
            if (v >= _n) return _siz;
            auto [t, u] = index(v);
            int res = __builtin_popcountll(_bs[t] & ((uint64_t(1) << u) - 1));
            for (; t; t &= t - 1) res += _d[t];
            return res;
        }


        int count_leq(int v) const { return count_lt(v + 1); }


        int count_gt(int v) const { return _siz - count_leq(v); }


        int count_geq(int v) const { return _siz - count_lt(v); }



        int kth_element(int k) const {

            if (not (0 <= k and k < _siz)) return -1;

            int t = 1 << _lg;



            for (int p = 1 << _lg >> 1; p; p >>= 1) {
                if (int nk = t <= _wn ? k - _d[t] : -1; nk >= 0) k = nk, t += p;
                else t -= p;
            }

            if (int nk = t <= _wn ? k - _d[t] : -1; nk >= 0) k = nk, ++t;
            --t;
            return (t << LOG_WORD) | kth_setbit(_bs[t], k);
        }


        int operator[](int k) const { return kth_element(k); }



        int max_leq(int v) const {
            if (v < 0) return -1;
            v = std::min(v, _n - 1);
            const auto [t, u] = index(v);
            const int lz = (WORD - 1) - u;
            if (const uint64_t bits = _bs[t] << lz >> lz) {
                return (t << LOG_WORD) | top_setbit(bits);
            }
            for (int i = 1; i <= SEARCH_WIDTH; ++i) {
                if (t - i < 0) return -1;
                if (_bs[t - i]) return ((t - i) << LOG_WORD) | top_setbit(_bs[t - i]);
            }
            return *--upper_bound(v);
        }


        int max_lt(int v) const { return max_leq(v - 1); }


        int min_geq(int v) const {
            if (v >= _n) return -1;
            v = std::max(v, 0);
            const auto [t, u] = index(v);
            if (const uint64_t bits = _bs[t] >> u << u) {
                return (t << LOG_WORD) | __builtin_ctzll(bits);
            }
            for (int i = 1; i <= SEARCH_WIDTH; ++i) {
                if (t + i >= _wn) return -1;
                if (_bs[t + i]) return ((t + i) << LOG_WORD) | __builtin_ctzll(_bs[t + i]);
            }
            return *lower_bound(v);
        }


        int min_gt(int v) const { return min_geq(v + 1); }
    private:
        struct IndexHolder {
            friend fenwick_tree_set;

            using difference_type = int;
            using value_type = int;
            using pointer = value_type*;
            using reference = value_type&;
            using iterator_category = std::random_access_iterator_tag;


            int index() const { return i; }

            bool has_value() const { return 0 <= i and i < ptr->size(); }


            IndexHolder& operator++() { return ++i, *this; }

            IndexHolder operator++(int) { IndexHolder ret = *this; ++(*this); return ret; }

            IndexHolder& operator--() { return --i, *this; }

            IndexHolder operator--(int) { IndexHolder ret = *this; --(*this); return ret; }

            IndexHolder& operator+=(difference_type dif) { return i += dif, *this; }

            friend IndexHolder operator+(IndexHolder it, difference_type dif) { it += dif; return it; }

            friend IndexHolder operator+(difference_type dif, IndexHolder it) { it += dif; return it; }

            IndexHolder& operator-=(difference_type dif) { return i -= dif, *this; }

            friend IndexHolder operator-(IndexHolder it, difference_type dif) { it -= dif; return it; }

            difference_type operator-(const IndexHolder &rhs) const { return i - rhs.i; }

            value_type operator[](difference_type i) const { return *((*this) + i); }

            value_type operator*() const { return ptr->kth_element(i); }

            bool operator!=(const IndexHolder &rhs) const { return i != rhs.i; }

            bool operator==(const IndexHolder &rhs) const { return i == rhs.i; }

            bool operator<(const IndexHolder &rhs) const { return i < rhs.i; }

            bool operator<=(const IndexHolder &rhs) const { return i <= rhs.i; }

            bool operator>(const IndexHolder &rhs) const { return i > rhs.i; }

            bool operator>=(const IndexHolder &rhs) const { return i >= rhs.i; }
        private:
            IndexHolder(const fenwick_tree_set* ptr, int i) : ptr(ptr), i(i) {}

            const fenwick_tree_set* ptr;
            int i;
        };
    public:
        using iterator = IndexHolder;
        using difference_type = iterator::difference_type;
        using value_type = iterator::value_type;
        using pointer = iterator::pointer;
        using reference = iterator::reference;


        iterator begin() const { return iterator(this, 0); }

        iterator end() const { return iterator(this, _siz); }

        iterator lower_bound(int v) const { return iterator(this, count_lt(v)); }

        iterator upper_bound(int v) const { return iterator(this, count_leq(v)); }

        iterator find(int v) const { return contains(v) ? lower_bound(v) : end(); }

        iterator erase(iterator it) { return erase(*it), it; }
    private:
        int _n, _wn, _lg, _siz;
        std::vector<int> _d;
        std::vector<uint64_t> _bs;

        template <typename Container, std::enable_if_t<is_container<Container>::value, std::nullptr_t> = nullptr>
        void construct_from_values(const Container &values) {
            for (int v : values) {
                assert(0 <= v and v < _n);
                const auto [t, u] = index(v);
                if ((_bs[t] >> u) & 1) continue;
                ++_siz;
                ++_d[t + 1];
                _bs[t] |= uint64_t(1) << u;
            }
            for (int i = 1; i <= _wn; ++i) {
                const int p = i + (-i & i);
                if (p <= _wn) _d[p] += _d[i];
            }
        }

        static constexpr int _large(int i) { return i >> LOG_WORD; }
        static constexpr int _small(int i) { return i & MASK_WORD; }
        static constexpr std::array<int, 2> index(int i) { return { _large(i), _small(i) }; }


        static constexpr int top_setbit(uint64_t x) { return (WORD - 1) - __builtin_clzll(x); }

        __attribute__((target("bmi2")))
        static int kth_setbit(uint64_t x, int k) { return __builtin_ctzll(_pdep_u64(uint64_t(1) << k, x)); }

        template <int k>
        void add(int v) {
            assert(0 <= v and v < _n);
            _siz += k;
            for (int t = _large(v) + 1; t <= _wn; t += -t & t) _d[t] += k;
        }
    };
}

#endif

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