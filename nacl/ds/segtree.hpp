struct segtree {
  using T = int;
  T f(T a, T b) { return a + b; } // any monoid operation
  static constexpr T ID = 0;      // identity element
  int n;
  vector<T> v;
  segtree(int n_) : n(n_), v(2 * n, ID) {}
  segtree(vector<T> &a) : n(a.size()), v(2 * n, ID) {
    copy_n(a.begin(), n, v.begin() + n);
    for (int i = n - 1; i > 0; i--)
      v[i] = f(v[i << 1], v[i << 1 | 1]);
  }
  void update(int i, T x) {
    for (v[i += n] = x; i /= 2;)
      v[i] = f(v[i << 1], v[i << 1 | 1]);
  }
  T query(int l, int r) {
    T tl = ID, tr = ID;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) tl = f(tl, v[l++]);
      if (r & 1) tr = f(v[--r], tr);
    }
    return f(tl, tr);
  }
};
