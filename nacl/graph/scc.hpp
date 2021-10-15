struct TarjanScc {
  int n, step;
  vector<int> time, low, instk, stk;
  vector<vector<int>> e, scc;
  TarjanScc(int n_)
      : n(n_), step(0), time(n), low(n), instk(n), e(n) {}
  void add_edge(int u, int v) { e[u].push_back(v); }
  void dfs(int x) {
    time[x] = low[x] = ++step;
    stk.push_back(x);
    instk[x] = 1;
    for (int y : e[x])
      if (!time[y]) {
        dfs(y);
        low[x] = min(low[x], low[y]);
      } else if (instk[y]) {
        low[x] = min(low[x], time[y]);
      }
    if (time[x] == low[x]) {
      scc.emplace_back();
      for (int y = -1; y != x;) {
        y = stk.back();
        stk.pop_back();
        instk[y] = 0;
        scc.back().push_back(y);
      }
    }
  }
  void solve() {
    for (int i = 0; i < n; i++)
      if (!time[i]) dfs(i);
    reverse(scc.begin(), scc.end());
    // scc in topological order
  }
};
