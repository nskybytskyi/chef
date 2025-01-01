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

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t; read(t); while (t--) {
    int n;
    string s;
    read(n, s);

    int balance = 0;
    map<int, int> count, len_sum;
    int le_count = 0, gt_count = 0;
    int64_t le_len_sum = 0, gt_len_sum = 0;
    int64_t le_bal_sum = 0, gt_bal_sum = 0;
    int64_t total = 0;

    for (int i = 0; i < n; ++i) {
      ++count[balance];
      ++le_count;
      len_sum[balance] += i;
      le_len_sum += i;

      if (s[i] == '0') {
        le_count -= count[balance];
        le_bal_sum -= le_count;
        le_len_sum -= len_sum[balance];
        gt_count += count[balance];
        gt_bal_sum += gt_count;
        gt_len_sum += len_sum[balance];
        --balance;
      } else {
        assert(s[i] == '1');
        ++balance;
        le_bal_sum += le_count;
        le_count += count[balance];
        le_len_sum += len_sum[balance];
        gt_bal_sum -= gt_count;
        gt_count -= count[balance];
        gt_len_sum -= len_sum[balance];
      }

      total += (le_bal_sum + le_count * (i + 1ll) - le_len_sum) / 2;
      total += (gt_bal_sum + gt_count * (i + 1ll) - gt_len_sum) / 2;
    }

    write(total);
  }
}