struct segment {
  struct node {
    int v = 0;
  };
  int m = 0;
  vector<node> t, p;
  segment(int n): m(n), t(4 * n), p(4 * n) {}
  void propagate(int tl, int tr, int n) {
    t[n].v += p[n].v * (tr - tl + 1);
    if (tl != tr) {
      p[2 * n].v += p[n].v;
      p[2 * n + 1].v += p[n].v;
    }
    p[n].v = 0;
  }
  void update(int l, int r, int v) {
    auto f = [&](auto &self, int l, int r, int tl, int tr, int n) -> void {
      propagate(tl, tr, n);
      if (l <= r) {
        if (tl == l && tr == r) {
          p[n].v += v;
          propagate(tl, tr, n);
        } else {
          int tm = (tl + tr) / 2;
          self(self, l, min(r, tm), tl, tm, 2 * n);
          self(self, max(l, tm + 1), r, tm + 1, tr, 2 * n + 1);
          auto &a = t[2 * n], &b = t[2 * n + 1];
          t[n].v = a.v + b.v;
        }
      }
    };
    f(f, l, r, 0, m - 1, 1);
  }
  int query(int l, int r) {
    auto f = [&](auto &self, int l, int r, int tl, int tr, int n) -> int {
      propagate(tl, tr, n);
      if (l > r) return 0;
      if (tl == l && tr == r) return t[n].v;
      int tm = (tl + tr) / 2;
      auto a = self(self, l, min(r, tm), tl, tm, 2 * n);
      auto b = self(self, max(l, tm + 1), r, tm + 1, tr, 2 * n + 1);
      return a + b;
    };
    return f(f, l, r, 0, m - 1, 1);
  }
};