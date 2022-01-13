#include "../math/number-theory/modular.hpp"
#pragma GCC target("popcnt")
#include <immintrin.h> // keep-line

void fwht(int n, vector<vector<Mod>> &a, bool inv) {
  for (int h = 0; h < n; h++)
    for (int i = 0; i < (1 << n); i++)
      if (!(i & (1 << h)))
        for (int k = 0; k <= n; k++)
          inv ? a[i | (1 << h)][k] -= a[i][k]
              : a[i | (1 << h)][k] += a[i][k];
}
// c[k] = sum(popcnt(i & j) == sz && i | j == k) a[i] * b[j]
vector<Mod> subset_convolution(int n, int sz,
                               const vector<Mod> &a_,
                               const vector<Mod> &b_) {
  int len = n + sz + 1, N = 1 << n;
  vector<vector<Mod>> a(1 << n, vector<Mod>(len, 0)), b = a;
  for (int i = 0; i < N; i++)
    a[i][_mm_popcnt_u64(i)] = a_[i],
    b[i][_mm_popcnt_u64(i)] = b_[i];
  fwht(n, a, 0), fwht(n, b, 0);
  for (int i = 0; i < N; i++) {
    vector<Mod> tmp(len);
    for (int j = 0; j < len; j++)
      for (int k = 0; k <= j; k++)
        tmp[j] += a[i][k] * b[i][j - k];
    a[i] = tmp;
  }
  fwht(n, a, 1);
  vector<Mod> c(N);
  for (int i = 0; i < N; i++)
    c[i] = a[i][_mm_popcnt_u64(i) + sz];
  return c;
}
