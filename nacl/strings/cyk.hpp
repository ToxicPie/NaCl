/// source: sunmoon (edited)

struct rule {
  // s -> xy
  // if y == -1, then s -> x (unit rule)
  int s, x, y, cost;
};
int state;
// state (id) for each letter (variable)
// lowercase letters are terminal symbols
map<char, int> rules;
vector<rule> cnf;
void init() {
  state = 0;
  rules.clear();
  cnf.clear();
}
// convert a cfg rule to cnf (but with unit rules) and add
// it
void add_to_cnf(char s, const string &p, int cost) {
  if (!rules.count(s)) rules[s] = state++;
  for (char c : p)
    if (!rules.count(c)) rules[c] = state++;
  if (p.size() == 1) {
    cnf.push_back({rules[s], rules[p[0]], -1, cost});
  } else {
    // length >= 3 -> split
    int left = rules[s];
    int sz = p.size();
    for (int i = 0; i < sz - 2; i++) {
      cnf.push_back({left, rules[p[i]], state, 0});
      left = state++;
    }
    cnf.push_back(
    {left, rules[p[sz - 2]], rules[p[sz - 1]], cost});
  }
}

constexpr int MAXN = 55;
vector<long long> dp[MAXN][MAXN];
// unit rules with negative costs can cause negative cycles
vector<bool> neg_INF[MAXN][MAXN];

void relax(int l, int r, rule c, long long cost,
           bool neg_c = 0) {
  if (!neg_INF[l][r][c.s] &&
      (neg_INF[l][r][c.x] || cost < dp[l][r][c.s])) {
    if (neg_c || neg_INF[l][r][c.x]) {
      dp[l][r][c.s] = 0;
      neg_INF[l][r][c.s] = true;
    } else {
      dp[l][r][c.s] = cost;
    }
  }
}
void bellman(int l, int r, int n) {
  for (int k = 1; k <= state; k++)
    for (rule c : cnf)
      if (c.y == -1)
        relax(l, r, c, dp[l][r][c.x] + c.cost, k == n);
}
void cyk(const string &s) {
  vector<int> tok;
  for (char c : s) tok.push_back(rules[c]);
  for (int i = 0; i < tok.size(); i++) {
    for (int j = 0; j < tok.size(); j++) {
      dp[i][j] = vector<long long>(state + 1, INT_MAX);
      neg_INF[i][j] = vector<bool>(state + 1, false);
    }
    dp[i][i][tok[i]] = 0;
    bellman(i, i, tok.size());
  }
  for (int r = 1; r < tok.size(); r++) {
    for (int l = r - 1; l >= 0; l--) {
      for (int k = l; k < r; k++)
        for (rule c : cnf)
          if (c.y != -1)
            relax(l, r, c,
                  dp[l][k][c.x] + dp[k + 1][r][c.y] +
                  c.cost);
      bellman(l, r, tok.size());
    }
  }
}

// usage example
int main() {
  init();
  add_to_cnf('S', "aSc", 1);
  add_to_cnf('S', "BBB", 1);
  add_to_cnf('S', "SB", 1);
  add_to_cnf('B', "b", 1);
  cyk("abbbbc");
  // dp[0][s.size() - 1][rules[start]] = min cost to
  // generate s
  cout << dp[0][5][rules['S']] << '\n'; // 7
  cyk("acbc");
  cout << dp[0][3][rules['S']] << '\n'; // INT_MAX
  add_to_cnf('S', "S", -1);
  cyk("abbbbc");
  cout << neg_INF[0][5][rules['S']] << '\n'; // 1
}
