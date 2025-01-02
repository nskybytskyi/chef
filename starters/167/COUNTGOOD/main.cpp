#ifndef IO_HPP
#define IO_HPP 1

#include <array>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace io {

void __read(char& c) { std::cin >> c; }
void __read(std::string& s) { std::cin >> s; }

template <typename T>
void __read_real(T& x) {
  std::string s;
  __read(s);
  x = std::stod(s);
}

template <typename T>
void __read_integer(T& x) {
  std::cin >> x;
}

void __read(int& x) { __read_integer(x); }
void __read(unsigned int& x) { __read_integer(x); }
void __read(long& x) { __read_integer(x); }
void __read(unsigned long& x) { __read_integer(x); }
void __read(long long& x) { __read_integer(x); }
void __read(unsigned long long& x) { __read_integer(x); }
void __read(double& x) { __read_real(x); }
void __read(long double& x) { __read_real(x); }

template <class U, class V>
void __read(std::pair<U, V>& p) {
  __read(p.first);
  __read(p.second);
}

template <size_t N=0, typename T>
void __read_tuple(T& t) {
  if constexpr (N < std::tuple_size<T>::value) {
    auto& x = std::get<N>(t);
    __read(x);
    __read_tuple<N + 1>(t);
  }
}
template <class... T>
void __read(std::tuple<T...>& t) {
  __read_tuple(t);
}

template <size_t N=0, typename T>
void __read(std::array<T, N>& a) {
  for (auto& x : a) {
    __read(x);
  }
}

template <class T>
void __read(std::vector<T>& v) {
  for (auto& x : v) {
    __read(x);
  }
}

void read() {}
template <class H, class... T>
void read(H& h, T&... t) {
  __read(h), read(t...);
}

void __write(const char c) {
  std::cout << c;
}

void __write(const std::string s) {
  for (char c : s) {
    __write(c);
  }
}

void __write(const char* s) {
  size_t len = strlen(s);
  for (size_t i = 0; i < len; ++i) {
    __write(s[i]);
  }
}

template <typename T>
void __write_integer(T x) {
  std::cout << x;
}

template <typename T>
void __write_real(T x) {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(15) << double(x);
  std::string s = oss.str();
  __write(s);
}

void __write(int x) { __write_integer(x); }
void __write(unsigned int x) { __write_integer(x); }
void __write(long x) { __write_integer(x); }
void __write(unsigned long x) { __write_integer(x); }
void __write(long long x) { __write_integer(x); }
void __write(unsigned long long x) { __write_integer(x); }
void __write(double x) { __write_real(x); }
void __write(long double x) { __write_real(x); }

template <class U, class V>
void __write(const std::pair<U, V> p) {
  __write(p.first);
  __write(' ');
  __write(p.second);
}

template <size_t N=0, typename T>
void __write_tuple(const T t) {
  if constexpr (N < std::tuple_size<T>::value) {
    if constexpr (N > 0) { __write(' '); }
    const auto x = std::get<N>(t);
    __write(x);
    __write_tuple<N + 1>(t);
  }
}
template <class... T>
void __write(std::tuple<T...> t) {
  __write_tuple(t);
}

template <class T, size_t S>
void __write(const std::array<T, S> a) {
  auto n = a.size();
  for (size_t i = 0; i < n; i++) {
    if (i) {
      __write(' ');
    }
    __write(a[i]);
  }
}

template <class T>
void __write(const std::vector<T> v) {
  auto n = v.size();
  for (size_t i = 0; i < n; i++) {
    if (i) {
      __write(' ');
    }
    __write(v[i]);
  }
}

template <class T>
void __write(const std::set<T> s) {
  __write(std::vector<T>{s.cbegin(), s.cend()});
}

template <class K, class V>
void __write(const std::map<K, V> m) {
  __write(std::vector<std::pair<K, V>>{m.cbegin(), m.cend()});
}

void write() { __write('\n'); }
template <class Head, class... Tail>
void write(Head&& head, Tail&&... tail) {
  __write(head);
  if (sizeof...(Tail)) {
    __write(' ');
  }
  write(std::forward<Tail>(tail)...);
}

}  // namespace io

#endif  // IO_HPP

#include <bits/stdc++.h>
using namespace std;
using namespace io;

constexpr auto bits = 64;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t; read(t); while (t--) {
    int64_t n, k;
    read(n, k);
    
    if (n == 1) {
      int q; read(q); while (q--) {
        int64_t l, r;
        read(l, r);
        write(l <= k && k <= r);
      }
      continue;
    }

    const int64_t lo = k, hi = k + n - 1;
    int64_t lcp = 0;
    int b = 0;
    for (int bit = bits - 1; bit >= 0; --bit) {
      if (((lo >> bit) & 1) == ((hi >> bit) & 1)) {
        lcp |= lo & (1ll << bit);
      } else {
        b = bit;
        break;
      }
    }
    
    vector<pair<int64_t, int64_t>> segs = {
      {lo, lcp + (1ll << b)},
      {lo + (1ll << b), lcp + (2ll << b) - 1}
    };

    for (int h = b - 1; h >= 0; --h) {
      if ((hi >> h) & 1) {
        segs[0].second += (2ll << h) - 1;
        break;
      }
    }

    segs[1].first = max(segs[1].first, segs[0].second + 1);

    int q; read(q); while (q--) {
      int64_t l, r;
      read(l, r);
      int64_t total = 0;
      for (const auto& [start, end] : segs) {
        if (start <= end) {
          total += max<int64_t>(0, min(end, r) - max(start, l) + 1);
        }
      }
      write(total);
    }
  }
}
