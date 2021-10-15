struct SPFA {
  static const int maxn = 1010, INF = 1e9;
  int dis[maxn];
  bitset<maxn> inq, inneg;
  queue<int> q, tq;
  vector<pii> v[maxn];
  void make_edge(int s, int t, int w) {
    v[s].emplace_back(t, w);
  }
  void dfs(int a) {
    inneg[a] = 1;
    for (pii i : v[a])
      if (!inneg[i.F]) dfs(i.F);
  }
  bool solve(int n, int s) { // true if have neg-cycle
    for (int i = 0; i <= n; i++) dis[i] = INF;
    dis[s] = 0, q.push(s);
    for (int i = 0; i < n; i++) {
      inq.reset();
      int now;
      while (!q.empty()) {
        now = q.front(), q.pop();
        for (pii &i : v[now]) {
          if (dis[i.F] > dis[now] + i.S) {
            dis[i.F] = dis[now] + i.S;
            if (!inq[i.F]) tq.push(i.F), inq[i.F] = 1;
          }
        }
      }
      q.swap(tq);
    }
    bool re = !q.empty();
    inneg.reset();
    while (!q.empty()) {
      if (!inneg[q.front()]) dfs(q.front());
      q.pop();
    }
    return re;
  }
  void reset(int n) {
    for (int i = 0; i <= n; i++) v[i].clear();
  }
};
