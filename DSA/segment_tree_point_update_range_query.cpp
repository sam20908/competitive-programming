struct segment {
  int m = 0;
  vector<int> t;
  segment(int n): m(n), t(4 * n) {}
  void update(int i, int v) {
    auto f = [&](auto &self, int tl, int tr, int n) -> void {
      if (tl == tr) t[n] = v;
      else {
        int tm = (tl + tr) / 2;
        if (i <= tm) self(self, tl, tm, 2 * n);
        else self(self, tm + 1, tr, 2 * n + 1);
        auto a = t[2 * n], b = t[2 * n + 1];
        t[n] = a + b;
      }
    };
    f(f, 0, m - 1, 1);
  }
  int query(int l, int r) {
    auto f = [&](auto &self, int l, int r, int tl, int tr, int n) -> int {
      if (l > r) return 0;
      if (tl == l && tr == r) return t[n];
      int tm = (tl + tr) / 2;
      auto a = self(self, l, min(r, tm), tl, tm, 2 * n);
      auto b = self(self, max(l, tm + 1), r, tm + 1, tr, 2 * n + 1);
      return a + b;
    };
    return f(f, l, r, 0, m - 1, 1);
  }
};