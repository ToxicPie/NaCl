/// source:
/// https://cp-algorithms.com/string/lyndon_factorization.html

vector<string> duval(string s) {
  // s += s for min rotation
  int n = s.size(), i = 0, ans;
  vector<string> res;
  while (i < n) { // change to i < n / 2 for min rotation
    ans = i;
    int j = i + 1, k = i;
    for (; j < n && s[k] <= s[j]; j++)
      k = s[k] < s[j] ? i : k + 1;
    while (i <= k) {
      res.push_back(s.substr(i, j - k));
      i += j - k;
    }
  }
  // min rotation is s.substr(ans, n / 2)
  return res;
}
