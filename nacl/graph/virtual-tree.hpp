#include "../ds/adamant-hld.hpp"

// id[u] is the index of u in pre-order traversal
vector<pii> build(vector<int> h) {
  sort(h.begin(), h.end(),
       [&](int u, int v) { return id[u] < id[v]; });
  int root = h[0], top = 0;
  for (int i : h) root = lca(i, root);
  vector<int> stk(h.size(), root);
  vector<pii> e;
  for (int u : h) {
    if (u == root) continue;
    int l = lca(u, stk[top]);
    if (l != stk[top]) {
      while (id[l] < id[stk[top - 1]])
        e.emplace_back(stk[top - 1], stk[top]), top--;
      e.emplace_back(stk[top], l), top--;
      if (l != stk[top]) stk[++top] = l;
    }
    stk[++top] = u;
  }
  while (top) e.emplace_back(stk[top - 1], stk[top]), top--;
  return e;
}
