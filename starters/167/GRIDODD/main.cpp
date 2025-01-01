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

void verify(const vector<vector<int>>& a, int n) {
  int s = 0;
  for (int i = 0; i < n; ++i) {
    s += a[i][i] + a[i][n - 1 - i];
  }
  vector<int> r(n), c(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      r[i] += a[i][j];
      c[j] += a[i][j];
    }
  }
  for (int i = 1; i < n; ++i) {
    assert(r[i - 1] + r[i] == s);
    assert(c[i - 1] + c[i] == s);
  }
}

vector<vector<int>> shift_with_diagonal(int n, int m) {
  vector a(n, vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      a[i][j] = ((i + j + m) % n) + 1;
    }
  }
  return a;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t; read(t); while (t--) {
    int n;
    read(n);
    assert(n & 1);
    const auto a = shift_with_diagonal(n, (n + 1) / 2);
    verify(a, n);
    for (const auto& row : a) {
      write(row);
    }
  }
}