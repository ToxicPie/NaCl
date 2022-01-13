constexpr ll MAXN = 2e5, INF = 2e18;
struct Line {
  ll m, b;
  Line() : m(0), b(-INF) {}
  Line(ll _m, ll _b) : m(_m), b(_b) {}
  ll operator()(ll x) const { return m * x + b; }
};
struct Li_Chao {
  Line a[MAXN * 4];
  void insert(Line seg, int l, int r, int v = 1) {
    if (l == r) {
      if (seg(l) > a[v](l)) a[v] = seg;
      return;
    }
    int mid = (l + r) >> 1;
    if (a[v].m > seg.m) swap(a[v], seg);
    if (a[v](mid) < seg(mid)) {
      swap(a[v], seg);
      insert(seg, l, mid, v << 1);
    } else insert(seg, mid + 1, r, v << 1 | 1);
  }
  ll query(int x, int l, int r, int v = 1) {
    if (l == r) return a[v](x);
    int mid = (l + r) >> 1;
    if (x <= mid)
      return max(a[v](x), query(x, l, mid, v << 1));
    else
      return max(a[v](x), query(x, mid + 1, r, v << 1 | 1));
  }
};
