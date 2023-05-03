/// source: mango_lassi
// stores integers in [0, 2^B)
// find(.+) finds first >=/<= i (or -1/2^B if none)
// space: ~2^B bits, time: 2^B init/clear, log B operation
template <int B, typename ENABLE = void> struct VEBTree {
  const static int K = B / 2, R = (B + 1) / 2, M = (1 << B);
  const static int S = 1 << K, MASK = (1 << R) - 1;
  array<VEBTree<R>, S> ch;
  VEBTree<K> act;
  int mi, ma;
  bool empty() const { return ma < mi; }
  int findNext(int i) const {
    if (i <= mi) return mi;
    if (i > ma) return M;
    int j = i >> R, x = i & MASK;
    int res = ch[j].findNext(x);
    if (res <= MASK) return (j << R) + res;
    j = act.findNext(j + 1);
    return (j >= S) ? ma : ((j << R) + ch[j].findNext(0));
  }
  int findPrev(int i) const {
    if (i >= ma) return ma;
    if (i < mi) return -1;
    int j = i >> R, x = i & MASK;
    int res = ch[j].findPrev(x);
    if (res >= 0) return (j << R) + res;
    j = act.findPrev(j - 1);
    return (j < 0) ? mi : ((j << R) + ch[j].findPrev(MASK));
  }
  void insert(int i) {
    if (i <= mi) {
      if (i == mi) return;
      swap(mi, i);
      if (i == M) ma = mi; // we were empty
      if (i >= ma) return; // we had mi == ma
    } else if (i >= ma) {
      if (i == ma) return;
      swap(ma, i);
      if (i <= mi) return; // we had mi == ma
    }
    int j = i >> R;
    if (ch[j].empty()) act.insert(j);
    ch[j].insert(i & MASK);
  }
  void erase(int i) {
    if (i <= mi) {
      if (i < mi) return;
      i = mi = findNext(mi + 1);
      if (i >= ma) {
        if (i > ma) ma = -1; // we had mi == ma
        return;              // after erase we have mi == ma
      }
    } else if (i >= ma) {
      if (i > ma) return;
      i = ma = findPrev(ma - 1);
      if (i <= mi) return; // after erase we have mi == ma
    }
    int j = i >> R;
    ch[j].erase(i & MASK);
    if (ch[j].empty()) act.erase(j);
  }
  void clear() {
    mi = M, ma = -1;
    act.clear();
    for (int i = 0; i < S; ++i) ch[i].clear();
  }
  template <class T>
  void init(const T &bts, int shift = 0, int s0 = 0,
            int s1 = 0) {
    s0 =
    -shift + bts.findNext(shift + s0, shift + M - 1 - s1);
    s1 =
    M - 1 -
    (-shift + bts.findPrev(shift + M - 1 - s1, shift + s0));
    if (s0 + s1 >= M) clear();
    else {
      act.clear();
      mi = s0, ma = M - 1 - s1;
      ++s0;
      ++s1;
      for (int j = 0; j < S; ++j) {
        ch[j].init(bts, shift + (j << R),
                   max(0, s0 - (j << R)),
                   max(0, s1 - ((S - 1 - j) << R)));
        if (!ch[j].empty()) act.insert(j);
      }
    }
  }
};
template <int B> struct VEBTree<B, enable_if_t<(B <= 6)>> {
  const static int M = (1 << B);
  ull act;
  bool empty() const { return !act; }
  void clear() { act = 0; }
  int findNext(int i) const {
    return ((i < M) && (act >> i))
           ? i + __builtin_ctzll(act >> i)
           : M;
  }
  int findPrev(int i) const {
    return ((i != -1) && (act << (63 - i)))
           ? i - __builtin_clzll(act << (63 - i))
           : -1;
  }
  void insert(int i) { act |= 1ull << i; }
  void erase(int i) { act &= ~(1ull << i); }
  template <class T>
  void init(const T &bts, int shift = 0, int s0 = 0,
            int s1 = 0) {
    if (s0 + s1 >= M) act = 0;
    else
      act = bts.getRange(shift + s0, shift + M - 1 - s1)
            << s0;
  }
};
