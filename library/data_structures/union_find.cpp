struct union_find {
  vector<int> p, s;
  union_find(int n) : p(n), s(n, 1) {
    iota(p.begin(), p.end(), 0);
  }
  int find(int i) {
    return p[i] == i ? i : find(p[i]);
  }
  void unite(
      int i,
      int j,
      function<void(int, int)> fn = [](int, int) {}) {
    i = find(i), j = find(j);
    if (i == j)
      return;
    if (s[i] < s[j])
      swap(i, j);
    if (fn)
      fn(i, j);
    s[i] += s[j];
    p[j] = i;
  }
};