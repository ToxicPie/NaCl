struct MCF {
  struct edge {
    ll to, from, cap, flow, cost, rev;
  } * fromE[MAXN];
  vector<edge> v[MAXN];
  ll n, s, t, flows[MAXN], dis[MAXN], pi[MAXN], flowlim;
  void make_edge(int s, int t, ll cap, ll cost) {
    if (!cap) return;
    v[s].pb(edge{t, s, cap, 0LL, cost, v[t].size()});
    v[t].pb(edge{s, t, 0LL, 0LL, -cost, v[s].size() - 1});
  }
  bitset<MAXN> vis;
  void dijkstra() {
    vis.reset();
    __gnu_pbds::priority_queue<pair<ll, int>> q;
    vector<decltype(q)::point_iterator> its(n);
    q.push({0LL, s});
    while (!q.empty()) {
      int now = q.top().second;
      q.pop();
      if (vis[now]) continue;
      vis[now] = 1;
      ll ndis = dis[now] + pi[now];
      for (edge &e : v[now]) {
        if (e.flow == e.cap || vis[e.to]) continue;
        if (dis[e.to] > ndis + e.cost - pi[e.to]) {
          dis[e.to] = ndis + e.cost - pi[e.to];
          flows[e.to] = min(flows[now], e.cap - e.flow);
          fromE[e.to] = &e;
          if (its[e.to] == q.end())
            its[e.to] = q.push({-dis[e.to], e.to});
          else q.modify(its[e.to], {-dis[e.to], e.to});
        }
      }
    }
  }
  bool AP(ll &flow) {
    fill_n(dis, n, INF);
    fromE[s] = 0;
    dis[s] = 0;
    flows[s] = flowlim - flow;
    dijkstra();
    if (dis[t] == INF) return false;
    flow += flows[t];
    for (edge *e = fromE[t]; e; e = fromE[e->from]) {
      e->flow += flows[t];
      v[e->to][e->rev].flow -= flows[t];
    }
    for (int i = 0; i < n; i++)
      pi[i] = min(pi[i] + dis[i], INF);
    return true;
  }
  pll solve(int _s, int _t, ll _flowlim = INF) {
    s = _s, t = _t, flowlim = _flowlim;
    pll re;
    while (re.F != flowlim && AP(re.F))
      ;
    for (int i = 0; i < n; i++)
      for (edge &e : v[i])
        if (e.flow != 0) re.S += e.flow * e.cost;
    re.S /= 2;
    return re;
  }
  void init(int _n) {
    n = _n;
    fill_n(pi, n, 0);
    for (int i = 0; i < n; i++) v[i].clear();
  }
  void setpi(int s) {
    fill_n(pi, n, INF);
    pi[s] = 0;
    for (ll it = 0, flag = 1, tdis; flag && it < n; it++) {
      flag = 0;
      for (int i = 0; i < n; i++)
        if (pi[i] != INF)
          for (edge &e : v[i])
            if (e.cap && (tdis = pi[i] + e.cost) < pi[e.to])
              pi[e.to] = tdis, flag = 1;
    }
  }
};
