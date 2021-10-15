/// source: KACTL
/// strings/SuffixArray.h

// sa[i]: starting index of suffix at rank i
//        0-indexed, sa[0] = n (empty string)
// lcp[i]: lcp of sa[i] and sa[i - 1], lcp[0] = 0
struct SuffixArray {
  vector<int> sa, lcp;
  SuffixArray(string &s,
              int lim = 256) { // or basic_string<int>
    int n = sz(s) + 1, k = 0, a, b;
    vector<int> x(all(s) + 1), y(n), ws(max(n, lim)),
    rank(n);
    sa = lcp = y, iota(all(sa), 0);
    for (int j = 0, p = 0; p < n;
         j = max(1, j * 2), lim = p) {
      p = j, iota(all(y), n - j);
      for (int i = 0; i < n; i++)
        if (sa[i] >= j) y[p++] = sa[i] - j;
      fill(all(ws), 0);
      for (int i = 0; i < n; i++) ws[x[i]]++;
      for (int i = 1; i < lim; i++) ws[i] += ws[i - 1];
      for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
      swap(x, y), p = 1, x[sa[0]] = 0;
      for (int i = 1; i < n; i++)
        a = sa[i - 1], b = sa[i],
        // clang-format off
        x[b] = (y[a] == y[b] && y[a + j] == y[b + j])
               ? p - 1 : p++;
      // clang-format on
    }
    for (int i = 1; i < n; i++) rank[sa[i]] = i;
    for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
      for (k &&k--, j = sa[rank[i] - 1];
           s[i + k] == s[j + k]; k++)
        ;
  }
};
