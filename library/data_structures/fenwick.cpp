struct fenwick {
  vector<int> t; // one-indexed
  int m;
  fenwick(int n) : t(n + 1), m(n + 1) {}
  int query(int i) {
    int ans = 0;
    for (; i > 0; i -= i & -i)
      ans += t[i];
    return ans;
  }
  void update(int i, int v) {
    for (; i < m; i += i & -i)
      t[i] += v;
  }
};