struct SAM {
  static const int maxc = 26;    // char range
  static const int maxn = 10010; // string len
  struct Node {
    Node *green, *edge[maxc];
    int max_len, in, times;
  } * root, *last, reg[maxn * 2];
  int top;
  Node *get_node(int _max) {
    Node *re = &reg[top++];
    re->in = 0, re->times = 1;
    re->max_len = _max, re->green = 0;
    for (int i = 0; i < maxc; i++) re->edge[i] = 0;
    return re;
  }
  void insert(const char c) { // c in range [0, maxc)
    Node *p = last;
    last = get_node(p->max_len + 1);
    while (p && !p->edge[c])
      p->edge[c] = last, p = p->green;
    if (!p) last->green = root;
    else {
      Node *pot_green = p->edge[c];
      if ((pot_green->max_len) == (p->max_len + 1))
        last->green = pot_green;
      else {
        Node *wish = get_node(p->max_len + 1);
        wish->times = 0;
        while (p && p->edge[c] == pot_green)
          p->edge[c] = wish, p = p->green;
        for (int i = 0; i < maxc; i++)
          wish->edge[i] = pot_green->edge[i];
        wish->green = pot_green->green;
        pot_green->green = wish;
        last->green = wish;
      }
    }
  }
  Node *q[maxn * 2];
  int ql, qr;
  void get_times(Node *p) {
    ql = 0, qr = -1, reg[0].in = 1;
    for (int i = 1; i < top; i++) reg[i].green->in++;
    for (int i = 0; i < top; i++)
      if (!reg[i].in) q[++qr] = &reg[i];
    while (ql <= qr) {
      q[ql]->green->times += q[ql]->times;
      if (!(--q[ql]->green->in)) q[++qr] = q[ql]->green;
      ql++;
    }
  }
  void build(const string &s) {
    top = 0;
    root = last = get_node(0);
    for (char c : s) insert(c - 'a'); // change char id
    get_times(root);
  }
  // call build before solve
  int solve(const string &s) {
    Node *p = root;
    for (char c : s)
      if (!(p = p->edge[c - 'a'])) // change char id
        return 0;
    return p->times;
  }
};
