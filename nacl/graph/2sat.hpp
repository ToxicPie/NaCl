#include "scc.hpp"

// 1 based, vertex in SCC = MAXN * 2
// (not i) is i + n
struct two_SAT {
  int n, ans[MAXN];
  SCC S;
  void imply(int a, int b) { S.make_edge(a, b); }
  bool solve(int _n) {
    n = _n;
    S.solve(n * 2);
    for (int i = 1; i <= n; i++) {
      if (S.scc[i] == S.scc[i + n]) return false;
      ans[i] = (S.scc[i] < S.scc[i + n]);
    }
    return true;
  }
  void init(int _n) {
    n = _n;
    fill_n(ans, n + 1, 0);
    S.init(n * 2);
  }
} SAT;
