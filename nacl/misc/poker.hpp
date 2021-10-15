#include <algorithm>
#include <array>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

struct hand {
  static constexpr auto rk = [] {
    array<int, 256> x{};
    auto s = "23456789TJQKACDHS";
    for (int i = 0; i < 17; i++) x[s[i]] = i % 13;
    return x;
  }();
  vector<pair<int, int>> v;
  vector<int> cnt, vf, vs;
  int type;
  hand() : cnt(4), type(0) {}
  void add_card(char suit, char rank) {
    ++cnt[rk[suit]];
    for (auto &[f, s] : v)
      if (s == rk[rank]) return ++f, void();
    v.emplace_back(1, rk[rank]);
  }
  void process() {
    sort(v.rbegin(), v.rend());
    for (auto [f, s] : v) vf.push_back(f), vs.push_back(s);
    bool str = 0, flu = find(all(cnt), 5) != cnt.end();
    if ((str = v.size() == 5))
      for (int i = 1; i < 5; i++)
        if (vs[i] != vs[i - 1] + 1) str = 0;
    if (vs == vector<int>{12, 3, 2, 1, 0})
      str = 1, vs = {3, 2, 1, 0, -1};
    if (str && flu) type = 9;
    else if (vf[0] == 4) type = 8;
    else if (vf[0] == 3 && vf[1] == 2) type = 7;
    else if (str || flu) type = 5 + flu;
    else if (vf[0] == 3) type = 4;
    else if (vf[0] == 2) type = 2 + (vf[1] == 2);
    else type = 1;
  }
  bool operator<(const hand &b) const {
    return make_tuple(type, vf, vs) <
           make_tuple(b.type, b.vf, b.vs);
  }
};
