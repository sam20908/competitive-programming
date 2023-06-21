template <typename T> struct segment {
  static T expand(int l, int r, T v) { return (r - l + 1) * v; }
  static T combine(T a, T b) { return a + b; }
  int m = 0;
  vector<T> tree;
  segment(int n) : m(n), tree(2 * n) {}
  void update(int i, T v) {
    auto f = [&](auto &self, int tl, int tr, int n) -> T {
      if (tr < i || tl > i || tl > tr)
        return T();
      if (tl == tr)
        return tree[n] += v;
      int mid = tl + (tr - tl) / 2;
      return tree[n] = self(self, tl, mid, n + 1) + self(self, mid + 1, tr, n + 2 * (mid - tl + 1));
    };
    f(f, 0, m - 1, 1);
  }
  T query(int l, int r) {
    auto f = [&](auto &self, int tl, int tr, int n) -> T {
      if (tr < l || tl > r || tl > tr)
        return T();
      if (tl >= l && tr <= r)
        return tree[n];
      int mid = tl + (tr - tl) / 2;
      return self(self, tl, mid, n + 1) + self(self, mid + 1, tr, n + 2 * (mid - tl + 1));
    };
    return f(f, 0, m - 1, 1);
  }
};