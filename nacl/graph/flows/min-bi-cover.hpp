#include "dinic.hpp"

// maximum independent set = all vertices not covered
// x : [0, n), y : [0, m]
struct Bipartite_vertex_cover {
  Dinic D;
  int n, m, s, t, x[maxn], y[maxn];
  void make_edge(int x, int y) { D.make_edge(x, y + n, 1); }
  int matching() {
    int re = D.max_flow(s, t);
    for (int i = 0; i < n; i++)
      for (Dinic::edge &e : D.v[i])
        if (e.to != s && e.flow == 1) {
          x[i] = e.to - n, y[e.to - n] = i;
          break;
        }
    return re;
  }
  // init() and matching() before use
  void solve(vector<int> &vx, vector<int> &vy) {
    bitset<maxn * 2 + 10> vis;
    queue<int> q;
    for (int i = 0; i < n; i++)
      if (x[i] == -1) q.push(i), vis[i] = 1;
    while (!q.empty()) {
      int now = q.front();
      q.pop();
      if (now < n) {
        for (Dinic::edge &e : D.v[now])
          if (e.to != s && e.to - n != x[now] && !vis[e.to])
            vis[e.to] = 1, q.push(e.to);
      } else {
        if (!vis[y[now - n]])
          vis[y[now - n]] = 1, q.push(y[now - n]);
      }
    }
    for (int i = 0; i < n; i++)
      if (!vis[i]) vx.pb(i);
    for (int i = 0; i < m; i++)
      if (vis[i + n]) vy.pb(i);
  }
  void init(int _n, int _m) {
    n = _n, m = _m, s = n + m, t = s + 1;
    for (int i = 0; i < n; i++)
      x[i] = -1, D.make_edge(s, i, 1);
    for (int i = 0; i < m; i++)
      y[i] = -1, D.make_edge(i + n, t, 1);
  }
};
