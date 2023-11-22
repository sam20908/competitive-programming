struct DSU {
  vector<int> p, s;
  DSU(int n): p(n), s(n, 1) {
    iota(p.begin(), p.end(), 0);
  }
  int find(int i) {
    return p[i] == i ? i : find(p[i]);
  }
  void unite(int i, int j) {
    i = find(i), j = find(j);
    if (i == j) return;
    if (s[i] < s[j]) swap(i, j);
    s[i] += s[j];
    p[j] = i;
  }
};
