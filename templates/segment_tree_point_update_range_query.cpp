template <typename T> struct segment {
  int m = 0;
  vector<T> tree;
  segment(int n): m(n), tree(4 * n) {}
  void update(int i, T v) {
    auto f = [&](auto &self, int tl, int tr, int n) -> void {
      if (tl == tr) tree[n] = v;
      else {
        int tm = (tl + tr) / 2;
        if (i <= tm) self(self, tl, tm, 2 * n);
        else self(self, tm + 1, tr, 2 * n + 1);
        tree[n] = tree[2 * n] + tree[2 * n + 1];
      }
    };
    f(f, 0, m - 1, 1);
  }
  T query(int l, int r) {
    auto f = [this](auto &self, int tl, int tr, int l, int r, int n) -> T {
      if (l > r) return 0;
      if (tl == l && tr == r) return tree[n];
      int tm = (tl + tr) / 2;
      return self(self, tl, tm, l, min(r, tm), 2 * n) + self(self, tm + 1, tr, max(l, tm + 1), r, 2 * n + 1);
    };
    return f(f, 0, m - 1, l, r, 1);
  }
};