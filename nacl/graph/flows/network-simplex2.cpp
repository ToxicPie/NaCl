struct NetworkSimplex {
  struct Edge {
    int a, b, c, k, f = 0;
  };

  int n;
  vector<int> pei, depth, dual;
  vector<Edge> E;
  vector<set<int>> tree;

  NetworkSimplex(int n)
      : n(n), pei(n + 1, -1), depth(n + 1, 0),
        dual(n + 1, 0), tree(n + 1) {}

  int AddEdge(int a, int b, int c, int k) {
    E.push_back({a, b, c, k});
    E.push_back({b, a, 0, -k});
    return E.size() - 2;
  }
  void dfs(int node) {
    for (auto ei : tree[node]) {
      if (ei == pei[node]) continue;
      int vec = E[ei].b;
      dual[vec] = dual[node] + E[ei].k;
      pei[vec] = (ei ^ 1);
      depth[vec] = 1 + depth[node];
      dfs(vec);
    }
  }
  template <typename CB> void walk(int ei, CB &&cb) {
    cb(ei);
    int a = E[ei].a, b = E[ei].b;
    while (a != b) {
      if (depth[a] > depth[b])
        cb(pei[a] ^ 1), a = E[pei[a]].b;
      else cb(pei[b]), b = E[pei[b]].b;
    }
  }
  long long Compute() {
    for (int i = 0; i < n; ++i) {
      int ei = AddEdge(n, i, 0, 0);
      tree[n].insert(ei);
      tree[i].insert(ei ^ 1);
    }

    long long answer = 0;
    int flow, cost, ein, eout, ptr = 0;
    const int B = 3 * n;
    for (int z = 0; z < E.size() / B + 1; ++z) {
      // Initialize tree tables.
      if (!z) dfs(n);
      // Find negative cycle (round-robin).
      pair<int, int> pin = {0, -1};
      for (int t = 0; t < B; ++t, (++ptr) %= E.size()) {
        auto &e = E[ptr];
        if (e.f < e.c)
          pin = min(
          pin, make_pair(dual[e.a] + e.k - dual[e.b], ptr));
      }
      tie(cost, ein) = pin;
      if (cost == 0) continue;
      // Pivot around ein.
      pair<int, int> pout = {E[ein].c - E[ein].f, ein};
      walk(ein, [&](int ei) {
        pout = min(pout, make_pair(E[ei].c - E[ei].f, ei));
      });
      tie(flow, eout) = pout;
      walk(ein, [&](int ei) {
        E[ei].f += flow, E[ei ^ 1].f -= flow;
      });
      tree[E[ein].a].insert(ein);
      tree[E[ein].b].insert(ein ^ 1);
      tree[E[eout].a].erase(eout);
      tree[E[eout].b].erase(eout ^ 1);
      // Update answer.
      answer += 1LL * flow * cost;
      z = -1;
    }
    return answer;
  }
};
