struct Aho_Corasick {
  static const int maxc = 26, maxn = 4e5;
  struct NODES {
    int Next[maxc], fail, ans;
  };
  NODES T[maxn];
  int top, qtop, q[maxn];
  int get_node(const int &fail) {
    fill_n(T[top].Next, maxc, 0);
    T[top].fail = fail;
    T[top].ans = 0;
    return top++;
  }
  int insert(const string &s) {
    int ptr = 1;
    for (char c : s) { // change char id
      c -= 'a';
      if (!T[ptr].Next[c]) T[ptr].Next[c] = get_node(ptr);
      ptr = T[ptr].Next[c];
    }
    return ptr;
  } // return ans_last_place
  void build_fail(int ptr) {
    int tmp;
    for (int i = 0; i < maxc; i++)
      if (T[ptr].Next[i]) {
        tmp = T[ptr].fail;
        while (tmp != 1 && !T[tmp].Next[i])
          tmp = T[tmp].fail;
        if (T[tmp].Next[i] != T[ptr].Next[i])
          if (T[tmp].Next[i]) tmp = T[tmp].Next[i];
        T[T[ptr].Next[i]].fail = tmp;
        q[qtop++] = T[ptr].Next[i];
      }
  }
  void AC_auto(const string &s) {
    int ptr = 1;
    for (char c : s) {
      while (ptr != 1 && !T[ptr].Next[c]) ptr = T[ptr].fail;
      if (T[ptr].Next[c]) {
        ptr = T[ptr].Next[c];
        T[ptr].ans++;
      }
    }
  }
  void Solve(string &s) {
    for (char &c : s) // change char id
      c -= 'a';
    for (int i = 0; i < qtop; i++) build_fail(q[i]);
    AC_auto(s);
    for (int i = qtop - 1; i > -1; i--)
      T[T[q[i]].fail].ans += T[q[i]].ans;
  }
  void reset() {
    qtop = top = q[0] = 1;
    get_node(1);
  }
} AC;
// usage example
string s, S;
int n, t, ans_place[50000];
int main() {
  Tie cin >> t;
  while (t--) {
    AC.reset();
    cin >> S >> n;
    for (int i = 0; i < n; i++) {
      cin >> s;
      ans_place[i] = AC.insert(s);
    }
    AC.Solve(S);
    for (int i = 0; i < n; i++)
      cout << AC.T[ans_place[i]].ans << '\n';
  }
}
