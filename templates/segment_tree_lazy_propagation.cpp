template <typename T> struct segment {
  static T expand(int l, int r, T v) { return (r - l + 1) * v; }
  static T combine(T a, T b) { return a + b; }
  int m = 0;
  vector<T> tree, lazy;
  segment(int n) : m(n), tree(2 * n), lazy(2 * n) {}
  T pushdown(int l, int r, T v, int n) {
    tree[n] = combine(expand(l, r, v), tree[n]);
    if (l != r) {
      int mid = l + (r - l) / 2;
      lazy[n + 1] = combine(lazy[n + 1], v);
      lazy[n + 2 * (mid - l + 1)] = combine(lazy[n + 2 * (mid - l + 1)], v);
    }
    lazy[n] = 0;
    return tree[n];
  }
  void update(int l, int r, T v) {
    auto f = [&](auto &self, int tl, int tr, int n) -> T {
      pushdown(tl, tr, lazy[n], n);
      if (tl > tr || l > tr || r < tl)
        return T();
      if (l <= tl && tr <= r) {
        return pushdown(tl, tr, v, n);
      } else {
        int mid = tl + (tr - tl) / 2;
        return tree[n] = combine(self(self, tl, mid, n + 1), self(self, mid + 1, tr, n + 2 * (mid - tl + 1)));
      }
    };
    f(f, 0, m - 1, 1);
  }
  T query(int l, int r) {
    auto f = [&](auto &self, int tl, int tr, int n) -> T {
      pushdown(tl, tr, lazy[n], n);
      if (tl > tr || l > tr || r < tl)
        return T();
      if (l <= tl && tr <= r) {
        return tree[n];
      } else {
        int mid = tl + (tr - tl) / 2;
        return combine(self(self, tl, mid, n + 1), self(self, mid + 1, tr, n + 2 * (mid - tl + 1)));
      }
    };
    return f(f, 0, m - 1, 1);
  }
};