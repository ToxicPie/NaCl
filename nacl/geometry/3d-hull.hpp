/// source: KACTL (+ modifications)

typedef Point3D<double> P3;

struct PR {
  void ins(int x) { (a == -1 ? a : b) = x; }
  void rem(int x) { (a == x ? a : b) = -1; }
  int cnt() { return (a != -1) + (b != -1); }
  int a, b;
};

struct F {
  int a, b, c;
};

// collinear points will kill it, please remove before use
// skip between -snip- comments if no 4 coplanar points
vector<F> hull3d(vector<P3> A) {
  int n = A.size(), t2 = 2, t3 = 3;
  vector<vector<PR>> E(n, vector<PR>(n, {-1, -1}));
  vector<F> FS;

  for (int i = 2; i < n; i++) // -snip-
    for (int j = i + 1; j < n; j++) {
      ll v = cross(A[0], A[1], A[i]).dot(A[j] - A[0]);
      if (v != 0) {
        if (v < 0) swap(i, j);
        swap(A[2], A[t2 = i]), swap(A[3], A[t3 = j]);
        goto ok;
      }
    }
  assert(!"all coplanar");
ok:; // -snip-

#define E(x, y) E[min(f.x, f.y)][max(f.x, f.y)]
#define C(a, b)                                            \
  if (E(a, b).cnt() != 2) mf(f.a, f.b, i);

  auto mf = [&](int i, int j, int k) {
    F f = {i, j, k};
    E(a, b).ins(k);
    E(a, c).ins(j);
    E(b, c).ins(i);
    FS.push_back(f);
  };

  auto in = [&](int i, int j, int k, int l) {
    P3 a = cross(A[i], A[j], A[l]),
       b = cross(A[j], A[k], A[l]),
       c = cross(A[k], A[i], A[l]);
    return a.dot(b) > 0 && b.dot(c) > 0;
  };
  mf(0, 2, 1), mf(0, 1, 3), mf(1, 2, 3), mf(0, 3, 2);

  for (int i = 4; i < n; i++) {
    for (int j = 0; j < FS.size(); j++) {
      F f = FS[j];
      ll d =
      cross(A[f.a], A[f.b], A[f.c]).dot(A[i] - A[f.a]);
      if (d > 0 || (d == 0 && in(f.a, f.b, f.c, i))) {
        E(a, b).rem(f.c);
        E(a, c).rem(f.b);
        E(b, c).rem(f.a);
        swap(FS[j--], FS.back());
        FS.pop_back();
      }
    }
    for (int j = 0, s = FS.size(); j < s; j++) {
      F f = FS[j];
      C(c, b);
      C(b, a);
      C(a, c);
    }
  }

  vector<int> idx(n), ri(n); // -snip-
  iota(idx.begin(), idx.end(), 0);
  swap(idx[t3], idx[3]), swap(idx[t2], idx[2]);
  for (int i = 0; i < n; i++) ri[idx[i]] = i;
  for (auto &[a, b, c] : FS)
    a = ri[a], b = ri[b], c = ri[c]; // -snip-
  return FS;
};
#undef E
#undef C
